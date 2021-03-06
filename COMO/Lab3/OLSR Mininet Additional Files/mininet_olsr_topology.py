from mininet.topo import Topo
from mininet.net import Mininet
from mininet.cli import CLI
from mininet.log import setLogLevel, info
from mininet.node import OVSController

class OlsrTopo(Topo):
	""" COMO OLSR topology """

	def __init__(self):
		"Create custom topo."

		# Initialize topology
		Topo.__init__(self)

		# Add hosts and switches
		pc1 = self.addHost('h1', mac='00:00:00:00:00:01')
		pc2 = self.addHost('h2', mac='00:00:00:00:00:02')
		pc3 = self.addHost('h3', mac='00:00:00:00:00:03')
		pc4 = self.addHost('h4', mac='00:00:00:00:00:04')
		pc5 = self.addHost('h5', mac='00:00:00:00:00:05')

		sw1 = self.addSwitch('s1')
		sw2 = self.addSwitch('s2')

		# Add links
		self.addLink(pc1, sw1)
		self.addLink(pc2, sw1)
		self.addLink(pc3, sw1)
		self.addLink(pc4, sw1)

		self.addLink(pc1, sw2)
		self.addLink(pc5, sw2)

def Olsr():
	topo= OlsrTopo()
	net = Mininet (topo=topo, controller = OVSController)
	net.start()

	for i in range(1,4):
		net.get('h'+str(i)).cmd('ifconfig h'+str(i)+'-eth0 inet6 add 2021::'+str(i)+'/128')
		net.get('h'+str(i)).cmd('echo 0 > /proc/sys/net/ipv6/conf/h'+str(i)+'-eth0/accept_ra')
		net.get('h'+str(i)).cmd('echo 1 > /proc/sys/net/ipv6/conf/h'+str(i)+'-eth0/forwarding')


	net.get('h1').cmd('ifconfig h1-eth1 up')
	net.get('h1').cmd('ifconfig h1-eth1 inet6 add 3000::1/64')

	net.get('h5').cmd('ifconfig h5-eth0 inet6 add3000::254/64')
	net.get('h5').cmd('route -A inet6 add 2021:0:0::/64 gw 3000::')
	info('Running\n')
	CLI(net)
	info('Stopping\n')
	net.stop()


if __name__ == '__main__':
	setLogLevel('info')
	Olsr()
