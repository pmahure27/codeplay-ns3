
## NS-3 Abstractions
### 1. NODE
- Generic Term for Hosts
- Basic _device Abstraction_ in NS3
- Represented by class ```Node``` in ```cpp```
- Computer to which we are **adding functionality**

### 2. Application 
- NS3 applications run on nodes to drive simulations
- Basic abstraction for a user program that **generates some activity to be simulated**
- Represented by class ```Application``` in ```cpp```
- _clients_ and _servers_ are one type of applications
>  *``` Application Class```*
> provides methods for **managing _representations_** of our version of user-level applications in simulations
### 3. Channel 
- Basic communicstion subnetwork abstraction
- Media over which **data flows** in networks
-  Represented by class ```Channel``` in ```cpp```
-  can model anything from a simple wire to a complex Ethernet Switch
>  *``` Channel Class```*
> provides methods for **managing _communication_** subnetwork objects and connecting nodes to them.
### 4. Net Device
- Enable the Node to **communicate** with other Nodes in the simulation via ```Channels```
- Analoguous to NIC in real-life
- Covers both the software driver and the simulated hardware
-  Represented by class ```NetDevice``` in ```cpp```
-  For a specific channel specific type of Net Device is used
>``` NetDevice Class```
>provides methods for **managing _connections_** to Node and Channel objects
### 5. Topology Helpers
- Enable to easily create a certain topology with given Nodes, Net Devices and Channels
> **Connections** In NS-3 Are :
> ```Nodes ---> Net Devices ```|| ``` NetDevices ---> Channels```

## Modules
- All included modules are present in ```ns-allinone-3.30.1/build/ns3```
- Usually included module file is used to include large number of modules just like how ``` bits/stdc++.h ``` does
## Logging 
**LOG Functionality** :  Macros which allow developers to send information to the ```std::clog``` output stream.
#### There are currently **seven** levels of log messages of increasing verbosity defined in the system.
>```NS_LOG_ERROR``` — Log error messages;
```NS_LOG_WARN``` — Log warning messages;
```NS_LOG_DEBUG``` — Log relatively rare, ad-hoc debugging messages;
```NS_LOG_INFO``` — Log informational messages about program progress;
```NS_LOG_FUNCTION``` — Log a message describing each function called;
```NS_LOG_LOGIC``` – Log messages describing logical flow within a function;
```NS_LOG_ALL``` — Log everything.

```cpp
NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");
```
- Define a Log component with a specific name 
- Allows you to enable and disable console message logging by reference to the name **FirstScriptExample**
- This macro defines a new "log component" which can be later selectively enabled or disabled with the **ns3::LogComponentEnable** and **ns3::LogComponentDisable** functions or with the _NS_LOG_ environment variable.

## First Tutorial Notes
 #### ``` Time::SetResolution(Time::NS)```
> - This is used to set smallest representable time (resolution) to nanoseconds(NS) 
>  - This can be done exactly once as this mechanism is memory hungry
> - Default time is 1 NS

#### ```NodeContainer nodes```
> - Creates object **nodes** of type NodeContainer
> - Represents a computer to which we are going to add stacks, peripheral cards and appplications
> - *Holds* the nodes we created
> - It's a topology helper
> #### Convenient way to create, access and manage any ```Node``` Object that we create to run the simulation 
#### ```PointToPointHelper pointToPoint;```
> -  The nodes as they stand in the script do nothing. 
> - The next step in constructing a topology is done by connecting our nodes together into a network
> - `helper` object is used to do the low-level work required to put the link together
> - Topology Helpers follow intimate coupling between **channels** and **net devices** and therefore a single  `PointToPointHelper` is used  to configure and connect  _ns-3_  ```PointToPointNetDevice```  and  `PointToPointChannel`  objects.
> - `PointToPointHelper` to do the work involved in creating, configuring and installing our devices for us.
>>```PointToPointHelper``` ===  ```PointToPointNetDevice``` ---> ```PointToPointChannel```

#### ```NetDeviceContainer devices ;```
> - We will need to have a list of all of the ```NetDevice``` objects that are created, so we use a ```NetDeviceContainer``` to hold them
> - The `Install` method of the `PointToPointHelper` takes a `NodeContainer` as a parameter. Internally, a `NetDeviceContainer` is created
>
After executing the `pointToPoint.Install  (nodes)` call we will have two nodes, each with an installed point-to-point net device and a single point-to-point channel between them.

#### ```InternternetStackHelper stack ;```
> - Currently we have two devices configured and having a channel for communication between them 
> - What we are lagging back in is a protocol stack to run over these devices
> - ```InternetStackHelper``` is used to install internet protocol suite (_TCP_, _IP_, _UDP_) over the devices/nodes

####  ```Ipv4AddressHelper address ;``` 
> - To associate devices on our network with an IP address
> - Helps in managing assigned addresses
>> ```cpp 
>>Ipv4InterfaceContainer interfaces = address.Assign (devices); 
>>```
>> Performs actual address assignment to devices
>
> #### Association between IP address and device is done using `IPv4Interface` object
> 
