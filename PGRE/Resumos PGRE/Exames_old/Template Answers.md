## Template PGRE 2020


1- False. *Default gateway* is a node that routes traffic destined to external networks to outside.

2- False. *ARP* converts **IP addresses to MAC address** -> used by higher level protocols/applications.

3- False. IPv6 has **128 bit length, grouped in 2 octet fields represented in hexadecimal notation**.

4- False (?). The great advantage of DNS is the possibility of **decentralized subdomain management** (independent management in subdomain1.domain.com and subdomain2.domain.com).

5- False. OSPF is an **internal** routing protocol, based on **link-state** paradigm.

6- False. 224.11.159.0 - 224.11.167.255 ->
		  224.11.10|011111.0 - 224.11.10|100111.255 -> mask of /32-(6+8)= /18 -> 225.225.192.0
		  Results in network 224.11.128.0/18 -> mask 225.225.192.0
		  
7- False. Hierarchy and directionality characterize **client-server**.

8- False. **Is not a % and represents the mean time between failures** (while the system is working correctly and as expected(.

9- False. **Not related to probes** and **in-band monitoring uses the same path for both prodution AND monitoring traffic**.

10- False. Capacity requirements relate to **rate-critical** applications and E-mail from the point of view of **delay** requirement is classified as being non-real time and asynchronous.


### Group II

1- RMON - Remote MONitoring - focus more on "flow-based" monitoring rather than a "device-based" one. A RMON implementatoin typically operates in a **server-client* model, where monitoring devices (probes) contain RMON software agents that collect information and analyse packets. 
**Advantages**: 
	- Allows remote monitoring.
	- Reduces SNMP traffic, since probes have more resposibility for data collection and processing.
	- Information only transmitted to management application when required - **push** instead of pull.

2- Areas: **FCAPS** - all areas need to be managed in order to have a complete monitoring process of the network. Procedures in **Fault Management** for example, might avoid a **Performance Management** procedure (reacting on a possible fault might be the key to not compromise system performance/SLA).
	* Fault Management:
			* Deals with the detection and location of faults/malfunctions.

	* Configuration Management:
			* Maintenance of software versions, system configuratioins and update/change scheduling.

	* Accounting Management:
			* Traffic accounting at network borders, detection of excessive traffic by users.
			* Detecting ineffective use of network resources.
			* Enables charges to be established for the use of resources -> **Biling**.

	* Perfomance Management:
			* Monitoring activities levels on the network, gather statistical information.
			* Control parameters to improve network perfomance -> **SLA verification** 

	* Security Management:
			* Protection of information, access to resources and event logging.

3- SNMPv3 mantains the model with 4 components of SNMPv1, but extends the security of the protocol by the following:
	* **Authentication**: origin identification, message integrity and response security aspects.
	* **Privacy**: data and message encryption.
	Providing both Authorization and access control to the system.
	

4- 
a) Because aspects such as delay, avaliability, reliability need to be takne in account.


b) Mission-critical: RMA requirements; Reliability, Maintainability and Availability
Rate-critical: capacity requirements
Real-time: delay requirements.

c) The flow type 20/80 (external/internal) was used in the early days of network managmente/development but due to the rise of the giant ammount of cloud base services and usage, and the confinement of local VLANs to simple switch blocks, the parttern is no longer true.
A 50/50 flow is closer to the reality (although the oposite 80/20 is starting to become more apparet).

d) Although 95% might seem like a lot, a service with a 95% daily availability is down 80 min (1h20), which is quite a lot for a "real" and traffic intense service. This can produce a lot of financial losses.

e) MTBF -> Mean time between failure, it's relevant in the reliability metric and is used to calculate the availability of a service in perfomance requirements.
