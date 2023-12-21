

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
#include <fstream>
#include <sstream>

using namespace std;

enum class Intensity{low, high};

class Module
{
    bool broadcasting_done;
    string module_id;
    vector<Module*> receivers;

    protected:
    Intensity pulse_to_broadcast;
    bool broadcasting_pending;

    public:
    Module(string module_id):broadcasting_done(false), module_id(module_id), pulse_to_broadcast(Intensity::low), broadcasting_pending(false){};
    void broadcast(Intensity pulse);
    void trigger_broadcast();
    virtual void receive_signal(Intensity pulse, string sender_id){
        cout << module_id <<":" << endl;
        broadcast(pulse);
        };
    bool is_broadcasting_done() {return broadcasting_done;}
    void reset() {broadcasting_done = false;}
    void register_receiver(Module* pRcvr){receivers.push_back(pRcvr);};
    string get_id() {return module_id;};
    virtual void set_sender(string sender_id);
    void print();
    virtual void print_senders();
};

queue<Module*> broadcast_order;
long long low_pulses = 0;
long long high_pulses = 0;

void Module::print()
{
    cout << module_id << " -> ";
    for(auto r : receivers)
    {
        cout << r->get_id() << ", ";
    }
    cout << endl;
}
void Module::set_sender(string sender_id)
{}

void Module::print_senders()
{}

void Module::broadcast(Intensity pulse)
{
    for(auto rcvr : receivers)
    {
     //   cout << "Module: " << module_id << " -" << (pulse == Intensity::low ? "low" :"high") << "-> " << rcvr->get_id() << endl;
        rcvr->receive_signal(pulse, module_id);
        broadcast_order.push(rcvr);
        if(pulse == Intensity::high)
        {
            high_pulses++;
        }
        else
        {
            low_pulses++;
        }
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
        cout << module_id << " broadcasting" << endl;
        broadcast(pulse_to_broadcast);
        broadcasting_pending = false;
    }
}

class FlipFlop: public Module
{
    bool state;
    public:
    FlipFlop(string module_id) : Module(module_id), state(false){};
    virtual void receive_signal(Intensity pulse, string sender_id);
};

void FlipFlop::receive_signal(Intensity pulse, string sender_id)
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
    map<string, Intensity> connected_senders;
    public:
    Conjunction(string module_id) : Module(module_id){};
    virtual void set_sender(string sender_id);
    virtual void receive_signal(Intensity pulse, string sender_id);
    virtual void print_senders();
};

void Conjunction::print_senders()
{
    cout << "Senders: ";
    for(auto s : connected_senders)
        cout << s.first << ", ";
    cout << endl;
}

void Conjunction::set_sender(string sender_id)
{
    connected_senders.emplace(make_pair(sender_id, Intensity::low));
}

void Conjunction::receive_signal(Intensity pulse, string sender_id)
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
/*Example input:
    int module_idx = 1;
    Module broadcaster("broadcaster");
    FlipFlop a("a");
    Conjunction inv("inv");
    FlipFlop b("b");
    Conjunction con("con");
    Module output("output");


    broadcaster.register_receiver(&a);
    a.register_receiver(&inv);
    a.register_receiver(&con);
    inv.register_receiver(&b);
    inv.set_sender(a.get_id());
    con.set_sender(a.get_id());
    b.register_receiver(&con);
    con.set_sender(b.get_id());
    con.register_receiver(&output);
*/

    ifstream ifs;
    string str;
    map<string,Module*> modules;

    ifs.open( "/Users/ivo/Coding/C++/AdventOfCode23/day20.txt", ios::in);
    if(ifs)
    {
        Module broadcaster("broadcaster");
        Module rx("rx");
       
        while(!ifs.eof())
        {
            getline(ifs, str);
            if(str[0] == '%')
            {
                string name = str.substr(1, 2);
                modules.emplace(name,new FlipFlop(name));
            }
            else if(str[0] == '&')
            {
                string name = str.substr(1, 2);
                modules.emplace(name,new Conjunction(name));
            }
        }

        ifs.clear();
        ifs.seekg(0);
        while(!ifs.eof())
        {
            stringstream ss;
            getline(ifs, str);
            if(string::npos == str.find("broadcaster"))
            {
                string m_name = str.substr(1, 2);
                auto md = modules.find(m_name);
                string::size_type pos = str.find('>');
                string params = str.substr(pos + 1);
                string name;
                ss << params;
                while(getline(ss, str,','))
                {
                    str = str.substr(1);
                    auto mdl = modules.find(str);
                    if(mdl != modules.end())
                    {
                        md->second->register_receiver(mdl->second);
                        mdl->second->set_sender(md->second->get_id());
                    }
                }
            }
            else
            {
                string::size_type pos = str.find('>');
                string params = str.substr(pos + 1);
                ss << params;
                while(getline(ss, str,','))
                {
                    str = str.substr(1);
                    auto mdl = modules.find(str);
                    if(mdl != modules.end())
                    {
                        broadcaster.register_receiver(mdl->second);
                    }
                }

            }
        }

        auto md = modules.find("tg");
        if(md != modules.end())
        {
            md->second->register_receiver(&rx);
        }

        // for(auto m : modules)
        // {
        //     m.second->print();
        //     m.second->print_senders();
        // }

        //simulate 1000 pushes
        for(int i = 0; i < 1000; i++)
        {
        // cout << "Push " << i+1 << endl;
            broadcaster.receive_signal(Intensity::low, "button");
            low_pulses++;
            for(;!broadcast_order.empty();broadcast_order.pop())
            {
                Module* mdl = broadcast_order.front();
                mdl->trigger_broadcast();
            }
        }
        cout << "High pulses: " << high_pulses << endl;
        cout << "Low pulses: " << low_pulses<< endl;
        cout << "Multiplied: " << high_pulses*low_pulses << endl;
    }
    
    return 0;
}