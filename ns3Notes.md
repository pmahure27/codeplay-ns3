## NS-3 Abstractions

### 1. NODE

- Generic Term for Hosts
- Basic _device Abstraction_ in NS3
- Represented by class `Node` in `cpp`
- Computer to which we are **adding functionality**

### 2. Application

- NS3 applications run on nodes to drive simulations
- Basic abstraction for a user program that **generates some activity to be simulated**
- Represented by class `Application` in `cpp`
- _clients_ and _servers_ are one type of applications
  > **`Application Class`**
  > provides methods for **managing _representations_** of our version of user-level applications in simulations

### 3. Channel

- Basic communicstion subnetwork abstraction
- Media over which **data flows** in networks
- Represented by class `Channel` in `cpp`
- can model anything from a simple wire to a complex Ethernet Switch
  > **`Channel Class`**
  > provides methods for **managing _communication_** subnetwork objects and connecting nodes to them.

### 4. Net Device

- Enable the Node to **communicate** with other Nodes in the simulation via `Channels`
- Analoguous to NIC in real-life
- Covers both the software driver and the simulated hardware
- Represented by class `NetDevice` in `cpp`
- For a specific channel specific type of Net Device is used
  > **`NetDevice Class`**
  > provides methods for **managing _connections_** to Node and Channel objects

### 5. Topology Helpers

- Enable to easily create a certain topology with given Nodes, Net Devices and Channels
  > **Connections** In NS-3 Are :
  > `Nodes ---> Net Devices`|| `NetDevices ---> Channels`

## Modules

- All included modules are present in `ns-allinone-3.30.1/build/ns3`
- Usually included module file is used to include large number of modules just like how `bits/stdc++.h` does

## Logging

**LOG Functionality** : Macros which allow developers to send information to the `std::clog` output stream.

#### There are currently **seven** levels of log messages of increasing verbosity defined in the system.

> `NS_LOG_ERROR` — Log error messages;
>
> > `NS_LOG_WARN` — Log warning messages;
> >
> > > `NS_LOG_DEBUG` — Log relatively rare, ad-hoc debugging messages;
> > >
> > > > `NS_LOG_INFO` — Log informational messages about program progress;
> > > >
> > > > > `NS_LOG_FUNCTION` — Log a message describing each function called;
> > > > >
> > > > > > `NS_LOG_LOGIC` – Log messages describing logical flow within a function;
> > > > > >
> > > > > > > `NS_LOG_ALL` — Log everything.

- #### `NS_LOG_UNCOND` : an unconditional logging macro that is _always displayed_ , irrespective of logging levels or component selection. (no associated log level).

```cpp
NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");
```

- Define a Log component with a specific name .
- Allows you to enable and disable console message logging by reference to the name **FirstScriptExample**.
- This macro defines a new "log component" which can be later selectively enabled or disabled with the **ns3::LogComponentEnable** and **ns3::LogComponentDisable** functions or with the _NS_LOG_ environment variable.
- For each `LOG_TYPE` there is also `LOG_LEVEL_TYPE` that, if used, enables logging of all the levels above it in addition to it’s level.

#### Command for extremely verbose Logging (_Logs all_) :

```bash
export 'NS_LOG=UdpEchoClientApplication=level_all|prefix_func: UdpEchoServerApplication=level_all|prefix_func'
```

## First Tutorial Notes

#### `Time::SetResolution(Time::NS)`

> - This is used to set smallest representable time (resolution) to nanoseconds(NS)
> - This can be done exactly once as this mechanism is memory hungry
> - Default time is 1 NS

#### `NodeContainer nodes`

> - Creates object **nodes** of type NodeContainer
> - Represents a computer to which we are going to add stacks, peripheral cards and appplications
> - _Holds_ the nodes we created
> - It's a topology helper
>
> #### Convenient way to create, access and manage any `Node` Object that we create to run the simulation

#### `PointToPointHelper pointToPoint;`

> - The nodes as they stand in the script do nothing.
> - The next step in constructing a topology is done by connecting our nodes together into a network
> - `helper` object is used to do the low-level work required to put the link together
> - Topology Helpers follow intimate coupling between **channels** and **net devices** and therefore a single `PointToPointHelper` is used to configure and connect _ns-3_ `PointToPointNetDevice` and `PointToPointChannel` objects.
> - `PointToPointHelper` to do the work involved in creating, configuring and installing our devices for us.
>   > `PointToPointHelper` === `PointToPointNetDevice` ---> `PointToPointChannel`

#### `NetDeviceContainer devices ;`

> - We will need to have a list of all of the `NetDevice` objects that are created, so we use a `NetDeviceContainer` to hold them
> - The `Install` method of the `PointToPointHelper` takes a `NodeContainer` as a parameter. Internally, a `NetDeviceContainer` is created
>
> After executing the `pointToPoint.Install (nodes)` call we will have two nodes, each with an installed point-to-point net device and a single point-to-point channel between them.

#### `InternternetStackHelper stack ;`

> - Currently we have two devices configured and having a channel for communication between them
> - What we are lagging back in is a protocol stack to run over these devices
> - `InternetStackHelper` is used to install internet protocol suite (_TCP_, _IP_, _UDP_) over the devices/nodes

#### `Ipv4AddressHelper address ;`

> - To associate devices on our network with an IP address
> - Helps in managing assigned addresses
>   > ```cpp
>   > Ipv4InterfaceContainer interfaces = address.Assign (devices);
>   > ```
>   >
>   > Performs actual address assignment to devices
>
> #### Association between IP address and device is done using `IPv4Interface` object

#### `Simulator::Run ();`

> - System starts looking through the list of scheduled events and executes them.
> - The Events are executed according to time specified or scheduled
> - the simulation proceeds by executing events in the temporal order of simulation time

### Stopping Simulation

- A processed event may generate zero or more events. So consumed event may generate more events to be consumed
- When event queue is empty simulation stops
- `Simulator: : Stop` can also cause simulation to stop
- It's necessary to call `Stop` in case of recurring events
  > Some Recurring Events are
  >
  > > - Flow Monitor - lost packet check
  > > - Periodic Broadcasters for updating Routing Tables

It is important to call `Simulator::Stop` _before_ calling `Simulator::Run`; otherwise, `Simulator::Run` may never return control to the main program to execute the stop !

## Command Line Arguments

Way to change how _ns-3_ scripts behave without editing and building is via _command line arguments_

### A. Overriding Defaults

1.  Declare command line parser

```cpp
int main (int argc, char *argv[])
{
 ...
 CommandLine cmd;
 cmd.Parse (argc, argv);
 ...
}
```

2.  Pass arguments with `./waf --run` command to the script

```bash
./waf --run "scratch/myfirst --PrintHelp"
```

#### Print Options Present as arguments :

> **`--PrintHelp`** : Print this help message.
> **`--PrintGroups`** : Print the list of groups.
> **`--PrintTypeIds`** : Print all TypeIds.
> **`--PrintGroup=[group]`** : Print all TypeIds of group.
> **`--PrintAttributes=[typeid]`** : Print all attributes of typeid.
> **`--PrintGlobals`** : Print the list of globals.

Example

```bash
./waf --run "scratch/myfirst --PrintAttributes=ns3::PointToPointNetDevice"
```

> #### - Prints all `Attributes` of this kind of Net Device

3.  To set attributes :
    > ```bash
    > ./waf --run "scratch/myfirst -- ns3::PointToPointNetDevice::DataRate=5Mbps"
    > ```
    >
    > The Example sets DataRate of channel to 5 Mb/s
4.  To find existing commands

- Most important command which can be used to identify if certain commands exist is **`--PrintGroup=[Group]`**
- Here `[Group]` is any module name from `src` directory of _ns-3_
- Example :

```bash
$ ./waf --run "scratch/myfirst --PrintGroup=PointToPoint"
TypeIds in group PointToPoint:
 ns3::PointToPointChannel
 ns3::PointToPointNetDevice
 ns3::PointToPointRemoteChannel
 ns3::PppHeader
```

### B. Hooking Own Values

- To add hooks `AddValue` method of `CommandLine` class is used

```cpp
int main (int argc, char *argv[])
{
uint32_t nPackets = 1;
CommandLine cmd;
cmd.AddValue("nPackets", "Number of packets to echo", nPackets);
cmd.Parse (argc, argv);
...
```

- To use them from command line set them as you set default attributes

```bash
$ ./waf --run "scratch/myfirst --nPackets=2"
```

- **Don't forget** to pass the argument to actual place where you set the attributes

```cpp
echoClient.SetAttribute ("MaxPackets", UintegerValue (nPackets));
```

## Tracing

- Standard C++ facilities can be used to generate output for tracing
- Logging is used to add structure

### Goals of tracing Subsystem

1. Allow user to generate **tracing for popular tracing sources** and **customize** which objects generate tracing
2. Extend tracing to **modify generated output format** or add new tracing sources without modifying core
3. **Modify core** to add new sources and sinks

#### A. Trace Sources

- Entities that can **signal events that happen** in a simulation and provide **access to interesting underlying data**
- A trace source could indicate when a packet is received by a net device and provide **access to the packet contents** for interested trace sinks
- Trace sources are **not useful by themselves**, they must be “connected” to other pieces of code that actually do something useful with the information provided by the sink

#### B. Trace Sinks

- **Consumers** of the events and data provided by the trace sources.
- A trace sink could print out interesting parts of the received packet from trace source

### ASCII Tracing

- Helper functionality wraps the low-level tracing system to **help with the details involved in configuring** some easily understood packet traces
- In ASCII Tracing output is in ASCII files
- Before calling `Simulator: :Run()` add following to the `.cc` file

```cpp
AsciiTraceHelper ascii;
pointToPoint.EnableAsciiAll (ascii.CreateFileStream ("myfirst.tr"));
```

- **`CreateFileStream()`** uses an unnamed object idiom to create a file stream object on the stack (without an object name) and pass it down to the called method.
- The outside call, to **`EnableAsciiAll()`** , tells the helper to enable ASCII tracing on all point-to-point devices present in simulation; and (provided) trace sinks **to write** out information about packet movement in _ASCII format_.

> #### Parsing ASCII traces
>
> - Each line corresponds to a trace event
> - Tracing events on the _transmit queue_ present in every `point-to-point` net device in the simulation.
> - The **transmit queue** is a queue through which every packet destined for a point-to-point channel must pass.
>   > \+ : _Enqueue_ operation on device queue
>   > \- : _Dequeue_ operarion
>   > d : _Dropped_ packet, as queue full
>   > r : Packet _received_

### PCAP Tracing

- **PCAP** : Packet Capture
- To enable _pcap_ tracing add following code after ASCII tracing :
  > ```cpp
  > pointToPoint.EnablePcapAll ("myfirst");
  > ```
- Here `myfirst` is a prefix
- For each device on each node, helper creates a `.pcap` trace file
- The name consist of :
  -- prefix
  -- node number
  -- device number
  -- _.pcap_ suffix

#### Reading output with `tcpdump`

- Use following command

```cpp
tcpdump -nn -tt -r {filename}.pcap
```

## Building Topologies

### Bus Topology

> **Note**
> A real Ethernet uses **CSMA/CD** (Carrier Sense Multiple Access with Collision Detection) scheme with exponentially increasing backoff to contend for the shared transmission medium.

### CSMA (Second Example)

```cpp
csmaNodes.Add (p2pNodes.Get (1));
```

> Gives the node **both** point-to-point and a CSMA Net device

```cpp
ApplicationContainer serverApps = echoServer.Install (csmaNodes.Get (nCsma));
```

> - The server application is installed at last CSMA node
> - The `Get()` gets last node from CSMA nodes container

Since we built an internetwork we need some form of internetwork routing.
**`GlobalRoutingHelper`** is be used to Provide internetwork routing

> #### `GlobalRoutingHelper`
>
> - Each node behaves as a OSPF router communicating instantly with all other routers
> - Each node generate link advertisement

> **Promiscuous Mode**
> The node in promiscuous mode sniffs network for all packets
>
> > ```cpp
> > csma.EnablePcap ("second", csmaDevices.Get (1), true);
> > ```
>
> places node in _promiscuous mode_ and makes it generate trace files for all other nodes/devices

### Wireless Network Topology

- _ns-3_ provides a _set of 802.11 models_ that attempt to provide an accurate MAC-level implementation of the 802.11 specification

#### `YansWifiChannelHelper channel = YansWifiChannelHelper::Default ();`

> - Create a channel object for WiFi
> - This channel carries the packets over the network
> - It's attributes determine characteristic of the network

#### `YansWifiPhyHelper phy = YansWifiPhyHelper::Default ();`

> - Create PHY layer object for WiFi
> - This object is associated with channel
> - The purpose of this object is make all WiFi devices to use same channel for communication
> - This is achieved by setting channel as `channel`
>   > ```cpp
>   > phy.SetChannel (channel.Create ());
>   > ```

#### `wifi.SetRemoteStationManager ("ns3::AarfWifiManager");`

> - `SetRemoteStationManager` is used to configure type of rate control algorithm to use
> - Here **AARF** algorithm is used for rate control
> - state of nodes is used to keep **track of association status**

```cpp
WifiMacHelper mac;
Ssid ssid = Ssid ("ns-3-ssid");
mac.SetType ("ns3::StaWifiMac",
  "Ssid", SsidValue (ssid),
  "ActiveProbing", BooleanValue (false));
```

> - Next, we configure the type of MAC, the SSID of the infrastructure network we want to setup and make sure that our stations don’t perform active probing
> - This code first creates an 802.11 service set identifier (SSID) object that will be used to set the value of the “Ssid” `Attribute` of the MAC layer implementation.
> - **ActiveProbing** `Attribute` is set to **false**. This means that probe requests will not be sent by MACs created by this helper.
