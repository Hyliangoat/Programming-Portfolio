import re
import string
import csv


def PrintAllItems():
    with open("ItemsPurchased.txt") as file: #Opens file, closes when done
        lines = file.readlines() #Reads lines
        lines = [line.rstrip() for line in lines] #Sorts lines into a list, while remove all spaces and \n

    tempList = set(lines) #Makes a set that does not allow copies of any word
    purchaseList = list(tempList) #Sets cannot be indexed so set is now turned back into a list
    
    print("These are the items purchased today:")
    for i in range(len(purchaseList)): #Goes through new, singular itemed list
        name = purchaseList[i] #Gets names
        count = lines.count(name) #Counts how many of the specified item is in the original list
        print(name, '---', count)


def PrintItem(v):

    with open("ItemsPurchased.txt") as file:
        lines = file.readlines()
        lines = [line.rstrip() for line in lines]

    count = lines.count(v) #Counts how many of the input item is in the original list
    return count

def PrintHistogram():
    
    with open("ItemsPurchased.txt") as file:
        lines = file.readlines()
        lines = [line.rstrip() for line in lines]

    tempList = set(lines)
    purchaseList = list(tempList)

    dataFile = open("frequency.dat", "w") #Opens file if one exists, creates file if none exist
    for i in range(len(purchaseList)): #Iterates through list
        name = purchaseList[i]
        count = lines.count(name)
        dataFile.write(f'{name} {count}') #Prints list to file in desired format


    
