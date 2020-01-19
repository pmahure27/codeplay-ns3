#include "ns3/command-line.h"
#include "ns3/config.h"
#include "ns3/uinteger.h"
#include "ns3/double.h"
#include "ns3/string.h"
#include "ns3/log.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/mobility-helper.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/yans-wifi-channel.h"
#include "ns3/mobility-model.h"
#include "ns3/olsr-helper.h"
#include "ns3/ipv4-static-routing-helper.h"
#include "ns3/ipv4-list-routing-helper.h"
#include "ns3/internet-stack-helper.h"
#include "ns3/netanim-module.h"


using namespace ns3;

int main(int argc, char const *argv[])
{
	NodeContainer c;
	c.Create(10);
	WifiHelper wifi;

	YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default();
  	wifiPhy.Set ("RxGain", DoubleValue (0) );
  // ns-3 supports RadioTap and Prism tracing extensions for 802.11b
  	wifiPhy.SetPcapDataLinkType (WifiPhyHelper::DLT_IEEE802_11_RADIO);
  	YansWifiChannelHelper wifiChannel;
  wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
  wifiChannel.AddPropagationLoss ("ns3::FriisPropagationLossModel");
  wifiPhy.SetChannel (wifiChannel.Create ());

  WifiMacHelper wifiMac;
  wifi.SetStandard (WIFI_PHY_STANDARD_80211b);
  wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager",
                                "DataMode",StringValue (phyMode),
                                "ControlMode",StringValue (phyMode));

  wifiMac.SetType ("ns3::AdhocWifiMac");
  NetDeviceContainer devices = wifi.Install (wifiPhy, wifiMac, c);

  mobility.SetPositionAllocator ("ns3::GridPositionAllocator",
                                 "MinX", DoubleValue (-100.0),
                                 "MinY", DoubleValue (-100.0),
                                 "DeltaX", DoubleValue (5.0),
                                 "DeltaY", DoubleValue (20.0),
                                 "GridWidth", UintegerValue (20),
                                 "LayoutType", StringValue ("RowFirst"));
  // each object will be attached a static position.
  // i.e., once set by the "position allocator", the
  // position will never change.
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");

  // finalize the setup by attaching to each object
  // in the input array a position and initializing
  // this position with the calculated coordinates.
  mobility.Install (c);
  AnimationInterface anim ("manet.xml");

  Simulator::Stop (Seconds (90.0));
  Simulator::Run ();
  Simulator::Destroy ();


	return 0;
}