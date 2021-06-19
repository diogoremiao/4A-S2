# Answers Test

## Challenges 5G

Depending on the traffic, 5G divides into 3 use-cases:

- eMMB (High Bitrate / Range)

- uRLLC (low latency high RMA)

- mmTC (massive number of devices)

It also provides a much bigger available bandwidth, as well as adaptive slot durations depending on the network.

All signal and information processing is done at the base stations.

It supports networks virtualization, as well as its functions for a easy to deploy topology.
It has a topology that slices the network into multiple layers with different functions.

C-RAN consists on splitting the base station functions into RRV and BBV, which enables inter-site scheduling and cooperation.

## Scheduling

Scheduling cam be done using a number of decision factors.

Round-Robin, all users are assigned the same amount fo resources, which can be wasteful and inefficient.

Max-Throughput schedules the user that has the highest SINR available, in order to maximize the networks global throughput.

Proportional-Fair schedules the user with the highest long-run throughput.

Mix-Max schedules the user with the lowest throughput at t-1.

## TDMA vs CDMA vs OFDMA

TDMA consists on dividing the channel into multiple time slots and assign them to individual users.
Each user will have a cyclically-repeated timeslot to transmit. The transmission is done at max bit rate as it uses the whole bandwidth but it not continuous..

CDMA consists on appling and orthogonal code to the signal, i.e, spread the information across the spectrum.
This results in individual signals that use the same frequency and are transmitted at the same time.

OFDMA is an extension of TDMA + FDMA, where the channel is separated into time-slots and frequency, as in a 2D pane.
This being, users will be assign a frequency and a timestamp to transmit their information.
The scheduling can be based on a number of rules (min-max, fair, RR, Max-TP)

## AODV vs OLSR

In ad-hoc networks, the mobility of the devices requires a different approach to routing, as routes will no be static.

One way is to use a reactive protocol, like AODV. This protocol only tries to find the route when a packet needs to be transmitted. For that purpose, it floods a packet requesting a route. Although it minimizes control traffic in the network, it is much slower at routing and therefore better in low mobility scenarios.

Another possibility is to use a proactive protocol, like OLSR. This protocol continuously updates the routing tables, by flooding HELLO messages to neighbor nodes in order to keep an updated table version. Although it does offer very low delay, it also has bandwidth issues regarding the control traffic generated in the network. It is therefore useful in high mobility, low traffic scenarios.

## Admission Control

The LTE admission control admits that a new arrival is characterized by Rj bit/s, requiring Nj blocks/frames to transmit.
If there are blocks available, including the ones already assigned, the call is accepted. The blocks are characterized by the frequency and the frame period.

The UMTS admission control admits that a new arrival is characterized by Rj bit/s. Depending on the transmission, a new arrival is characterized by a load factor that is related to the interference caused by the transmission. If the total load factor is smaller than a previously set threshold, then the call is accepted.

