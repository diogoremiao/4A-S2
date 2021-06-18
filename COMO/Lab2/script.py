import array as arr

def main():
    
    print("Opening file")
    f = open("5sites.txt", "r")

    rx_db=arr.array('d',[])
    rx_neg=arr.array('d',[])
    rx_0=arr.array('d',[])
    rx_10=arr.array('d',[])
    rx_20=arr.array('d',[])
    rx_30=arr.array('d',[])
    rx_40=arr.array('d',[])
    rx_50=arr.array('d',[])
    rx_60=arr.array('d',[])

    best_unit=arr.array('i',[])

    count_sardoura = 0
    count_resende = 0
    count_monte = 0
    count_antena_1 = 0
    count_antena_2 = 0

    aux = 0
    #read file
    for x in f:
        entry = x
        entry_split = entry.split("\t")

        if entry_split[0] == 'Latitude':
            aux = 1
            continue
        
        if aux == 1:
            rx_value = entry_split[2].replace(" ","")
            rx_value = rx_value.replace(",",".")
            rx_db.append(float(rx_value))

            best_unit.append(int(entry_split[3]))


    print("Closing file")
    f.close()


    #sort data
    for x in rx_db:
        if x < 0:
            rx_neg.append(x)

        elif x < 10:
            rx_0.append(x)
        
        elif x < 20:
            rx_10.append(x)

        elif x < 30:
            rx_20.append(x)

        elif x < 40:
            rx_30.append(x)

        elif x < 50:
            rx_40.append(x)

        elif x < 60:
            rx_50.append(x)
        
        elif x > 60:
            rx_60.append(x)


    for x in best_unit:
        if x == 4:
            count_sardoura+=1

        if x == 5:
            count_resende+=1

        if x == 3:
            count_monte+=1

        if x == 9:
            count_antena_1+=1

        if x == 10:
            count_antena_2+=1


    print("Percentage of area without coverage:","%.2f" % (len(rx_neg)/len(rx_db)*100), "%")
    print("Percentage of area with low coverage:","%.2f" % ((len(rx_neg)+len(rx_0))/len(rx_db)*100), "%")

    print("Percentage of area with coverage [0-10]:","%.2f" % (len(rx_0)/len(rx_db)*100), "%")
    print("Percentage of area with coverage [10-20]:","%.2f" % (len(rx_10)/len(rx_db)*100), "%")
    print("Percentage of area with coverage [20-30]:","%.2f" % (len(rx_20)/len(rx_db)*100), "%")
    print("Percentage of area with coverage [30-40]:","%.2f" % (len(rx_30)/len(rx_db)*100), "%")
    print("Percentage of area with coverage [40-50]:","%.2f" % (len(rx_40)/len(rx_db)*100), "%")
    print("Percentage of area with coverage [50-60]:","%.2f" % (len(rx_50)/len(rx_db)*100), "%")
    print("Percentage of area with coverage [60+]:","%.2f" % (len(rx_60)/len(rx_db)*100), "%")

    print("Location with sites 1 and 2 as optimal receivers:",count_antena_1+count_antena_2)
    print("Locations with site 1 as optimal receiver", count_antena_1)
    print("Locations with site 2 as optimal receiver", count_antena_2)





if __name__ == "__main__":
    main()