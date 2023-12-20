

/*

enum class Intensity{low, high};

class Module
{
    broadcaster_idx
    broadcast 
    //when the broadcast to all is done
    bool broadcasting_done
}

class FlipFlop::Module
{
    //state = off
    bool state = false;
    
    receive(Intensity pulse)
    {
        if(pulse == Intensity::low)
        {
            if(state == true)
                broadcast(Intensity::low);
            else
                broadcast(Intensity::high);
            state = !state;
        }
    }
}

class Broadcaster::Module

class Conjunction::Module
{
    array connected_modules
    subscribe_sender

    receive(int broadcaster_idx)
    {
        if(connected_module == broadcaster_idx)
        {
            pulse_received(connected_module
        }
    }

    broadcast
    {
        if all connected modules == Intensity::high
            broadcast(intensity::low)
        else
            broadcast(intensity::high)
    }
}

module
*/
#include <map>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

enum class Intensity{low, high};



class Module
{
    bool broadcasting_done;
    int module_id;
    vector<Module*> receivers;

    protected:
    Intensity pulse_to_broadcast;
    bool broadcasting_pending;

    public:
    Module(int module_id):broadcasting_done(false), module_id(module_id), broadcasting_pending(false), pulse_to_broadcast(Intensity::low){};
    void broadcast(Intensity pulse);
    void trigger_broadcast();
    virtual void receive_signal(Intensity pulse, int sender_id){broadcast(pulse);};
    bool is_broadcasting_done() {return broadcasting_done;}
    void reset() {broadcasting_done = false;}
    void register_receiver(Module* pRcvr){receivers.push_back(pRcvr);};
    int get_id() {return module_id;};
};

queue<Module*> broadcast_order;

void Module::broadcast(Intensity pulse)
{
    for(auto rcvr : receivers)
    {
        cout << "Module: " << module_id << " -" << (pulse == Intensity::low ? "low" :"high") << "-> " << rcvr->get_id() << endl;
        rcvr->receive_signal(pulse, module_id);
        broadcast_order.push(rcvr);
    }
    // for(auto rcvr : receivers)
    // {
    //     rcvr->trigger_broadcast();
    // }
    // broadcasting_done = true;
}

void Module::trigger_broadcast()
{
    if(broadcasting_pending)
    {
        broadcast(pulse_to_broadcast);
        broadcasting_pending = false;
    }
}

class FlipFlop: public Module
{
    bool state;
    public:
    FlipFlop(int module_id) : Module(module_id), state(false){};
    virtual void receive_signal(Intensity pulse, int sender_id);
};

void FlipFlop::receive_signal(Intensity pulse, int sender_id)
{
    if(pulse == Intensity::low)
    {
        if(state == true)
            pulse_to_broadcast = Intensity::low;
        else
            pulse_to_broadcast =  Intensity::high;
        state = !state;
        broadcasting_pending = true;
    }    
}

class Conjunction: public Module
{
    map<int, Intensity> connected_senders;
    public:
    Conjunction(int module_id) : Module(module_id){};
    void set_sender(int sender_id) {connected_senders.emplace(make_pair(sender_id, Intensity::low));};
    virtual void receive_signal(Intensity pulse, int sender_id);
};

void Conjunction::receive_signal(Intensity pulse, int sender_id)
{
    auto sender = connected_senders.find(sender_id);
    if(sender != connected_senders.end())
        sender->second = pulse;

    bool b_send_low = true;
    for(auto sender : connected_senders)
    {
        if(sender.second == Intensity::low)
        {
            b_send_low = false;
            break;
        }
    }
    if(b_send_low)
        pulse_to_broadcast = Intensity::low;
    else
        pulse_to_broadcast = Intensity::high;

    broadcasting_pending = true;
}

int main()
{
/*
broadcaster -> a
%a -> inv, con
&inv -> b
%b -> con
&con -> output
*/
    int module_idx = 1;
    Module broadcaster(module_idx++);
    FlipFlop a(module_idx++);
    Conjunction inv(module_idx++);
    FlipFlop b(module_idx++);
    Conjunction con(module_idx++);
    Module output(module_idx++);

    //vector<Module*> modules = {&a, &inv, &con, &b};


    broadcaster.register_receiver(&a);
    a.register_receiver(&inv);
    a.register_receiver(&con);
    inv.register_receiver(&b);
    inv.set_sender(a.get_id());
    con.set_sender(a.get_id());
    b.register_receiver(&con);
    con.set_sender(b.get_id());
    con.register_receiver(&output);
    //a.register_receiver

    //simulate 4 pushes
    for(int i = 0; i < 4; i++)
    {
        cout << "Push " << i+1 << endl;
        broadcaster.receive_signal(Intensity::low, 0);
        for(;!broadcast_order.empty();broadcast_order.pop())
        {
            Module* mdl = broadcast_order.front();
            mdl->trigger_broadcast();
        }
      //  broadcast_order.clear();
    }
    return 0;
}