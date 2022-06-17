import pandas as pd
import numpy as np
import os
import re

def readFile():
    dane = []
    isAtEnd = lambda c : line[-1] == c
    with open("result.csv", encoding='utf8', mode='r') as file:
        for line in file:
            line = line.strip()
            dane.append(line[:-1])
            if   isAtEnd('A'):
                dane[-1] += "1"
            elif isAtEnd('B'):
                dane[-1] += "2"
            elif isAtEnd('C'):
                dane[-1] += "3"
            elif isAtEnd('D'):
                dane[-1] += "4"
    return dane

def writeFile(data):
    with open('pytania.csv', encoding='utf8', mode='w+') as file:
        for element in data[1:]:
            file.write(element + '\n')

def fileHandle():
    try:
        data = readFile()
        writeFile(data)
    except OSError:
        print("Problem z otwarciem pliku")


def buildCsv():
    Q_COUNT = 10
    STAGE_COUNT = 15

    colName = ['QUESTION', 'ANSWER1', 'ANSWER2', 'ANSWER3', 'ANSWER4', 'CORRECT_ANSWER']
    pd.options.display.max_columns = 20
    pd.options.display.width = 500
    data = pd.read_csv('pytania.csv', names=colName)
    data.insert(0, 'ID', np.arange(1, len(data) + 1, 1), allow_duplicates=False)


    csvNum = 0
    dirNum = 1
    directory = "pytania_1"
    os.makedirs(directory)

    for i in range(0, len(data), Q_COUNT):
        dataShort = data[i:i+Q_COUNT]
        dataShort = dataShort.replace(np.arange(i + 1, i + Q_COUNT + 1), np.arange(1, Q_COUNT+1))
        csvNum %= STAGE_COUNT
        dataShort.to_csv(f"{directory}/{str(csvNum + 1)}.csv", encoding='utf-8', index=False)
        csvNum += 1
        if csvNum == STAGE_COUNT:
            dirNum += 1
            directory = f"pytania_{str(dirNum)}"
            os.makedirs(directory)

def changeQuotes():
    pd.options.display.max_colwidth = 100
    pd.options.display.max_columns = 30
    pd.options.display.width = 500
    folder = "stages_new"

    for numFile in range(1, 16):
        file = f"{folder}/{numFile}.csv"
        data = pd.read_csv(file)
        txt = data.replace("„", "”", regex=True)
        txt.to_csv(f"stages_new/{numFile}.csv", encoding='utf-8', index=False)

def main():
        # fileHandle()
        # buildCsv()
        # changeQuotes()
        pass

if __name__ == '__main__':
    main()