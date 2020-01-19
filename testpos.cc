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

static void CourseChange (std::string foo, Ptr<const MobilityModel> mobility)
{
  Vector pos = mobility->GetPosition ();
  Vector vel = mobility->GetVelocity ();
  std::cout << Simulator::Now () << ", model=" << mobility << ", POS: x=" << pos.x << ", y=" << pos.y
            << ", z=" << pos.z << "; VEL:" << vel.x << ", y=" << vel.y
            << ", z=" << vel.z << std::endl;
}


int main(int argc, char const *argv[])
{

	Config::SetDefault ("ns3::RandomWalk2dMobilityModel::Mode", StringValue ("Time"));
  Config::SetDefault ("ns3::RandomWalk2dMobilityModel::Time", StringValue ("2s"));
  Config::SetDefault ("ns3::RandomWalk2dMobilityModel::Speed", StringValue ("ns3::ConstantRandomVariable[Constant=1.0]"));
  Config::SetDefault ("ns3::RandomWalk2dMobilityModel::Bounds", StringValue ("0|500|0|500"));

  
	NodeContainer c;
	c.Create(50);
	NodeContainer d;
	d.Create(50);
	WifiHelper wifi;
	std::string phyMode("DsssRate1Mbps");
	 Config::SetDefault ("ns3::WifiRemoteStationManager::NonUnicastMode",
                      StringValue (phyMode));

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
  //NetDeviceContainer devices = wifi.Install (wifiPhy, wifiMac, c);

  MobilityHelper mobility;
  mobility.SetPositionAllocator ("ns3::RandomDiscPositionAllocator",
                                 "X", StringValue ("200.0"),
                                 "Y", StringValue ("80.0"),
                                 "Rho", StringValue ("ns3::UniformRandomVariable[Min=30|Max=60]"));
  mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                             "Mode", StringValue ("Time"),
                             "Time", StringValue ("2s"),
                             "Speed", StringValue ("ns3::ConstantRandomVariable[Constant=1.0]"),
                             "Bounds", StringValue ("0|500|0|500"));
  //mobility.InstallAll ();
  Config::Connect ("/NodeList/*/$ns3::MobilityModel/CourseChange",MakeCallback (&CourseChange));

  // finalize the setup by attaching to each object
  // in the input array a position and initializing
  // this position with the calculated coordinates.


  MobilityHelper mobility1;
  mobility1.SetPositionAllocator ("ns3::RandomDiscPositionAllocator",
                                 "X", StringValue ("70.0"),
                                 "Y", StringValue ("80.0"),
                                 "Rho", StringValue ("ns3::UniformRandomVariable[Min=30|Max=60]"));
  mobility1.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                             "Mode", StringValue ("Time"),
                             "Time", StringValue ("2s"),
                             "Speed", StringValue ("ns3::ConstantRandomVariable[Constant=1.0]"),
                             "Bounds", StringValue ("0|500|0|500"));
  //Config::Connect ("/NodeList/*/$ns3::MobilityModel/CourseChange",MakeCallback (&CourseChange));

  mobility.Install (c);
  mobility1.Install (d);
  AnimationInterface anim ("manet.xml");

  Simulator::Stop (Seconds (90.0));
  Simulator::Run ();
  Simulator::Destroy ();


	return 0;
}