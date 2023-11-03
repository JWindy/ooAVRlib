#--------------------------------------------------------------------
# Description:  Checks all #include of local libraries and the required 
#               version of the libraries in header and source file of a 
#               new project and copies all libreries in the ./lib folder.
#  
# Author:       Johannes Windmiller
# 
# Version:      v0.1
# 
# History:      v0.1     Initial implementation
# 
# Copyright:    see LICENSE_software.md in GitHub root folder
#
# Requirements for versioning in header and source file
#   - all #include of local libraries must be followed by //v<ma.mi>
#   - #includes can be added in the source or header file
#   - #include must start in the first 5 columns of a line
#   - the version of the library must be defined in the .cpp file using the 
#     ver_t struct definded in libUtility.h 
#--------------------------------------------------------------------

import os
import shutil

listOfRequiredLibs = []
processedLibs = []
listSubDirPath = []
errorMessages = []

workingDirectory = os. getcwd() ;

def fctSearchForLibsInFile(file):
    if file[-1] == "h":
        currentLib = file[file.rfind('/')+1:-2]
    else:
        currentLib = file[file.rfind('/')+1:-4]
    fileHandle = open(file, 'rb')
    for lineByte in fileHandle.readlines():
        line = str(lineByte)
        if line.find("#include") < 5 and line.find("#include") >= 0:#string might be used somewhere else, but hopefully not in the first few columns
            if line.find('"') != -1: #only local libs
                libName = line[line.find('"')+1:line.rfind('"')-2]
                if libName != currentLib:
                    if line.find("//v") != -1:
                        libVersion = line[line.find("//v")+3:]
                        libVersion = libVersion[:libVersion.find(".")+2]
                    else:
                        libVersion = "Nan"    
                    print("\t" + libName + " v" + libVersion)
                    newLib = [libName, libVersion]
                    appendNewLib = True
                    #check, if lib is already in list
                    for lib in listOfRequiredLibs:
                        if newLib in lib:
                            appendNewLib = False
                            break
                    for lib in processedLibs:
                        if newLib in lib:
                            appendNewLib = False
                            break
                    if appendNewLib:
                        listOfRequiredLibs.append(newLib)
    fileHandle.close()
    
def getLibVersion(file):
    fileHandle = open(file, 'rb')
    major = -1
    minor = -1
    for lineByte in fileHandle.readlines():
        line = str(lineByte)
        if "version.major" in line:
            line = line[line.find("= ")+2:-1]
            if ";" in line:
                line = line[:line.find(";")]#in case there is a comment or what ever behind the ;
            major = line
        elif "version.minor" in line:
            line = line[line.find("= ")+2:-1]
            if ";" in line:
                line = line[:line.find(";")]
            minor = line
    version = str(major) + "." + str(minor)
    return version
            
#---------------------------------------------------------
#main
#---------------------------------------------------------

#select target project
print("Select project directory to copy libs to:")
index = 0
for subdir in os.listdir(workingDirectory):
    if(subdir[-2:]==".X"):
        listSubDirPath.append(workingDirectory + "/" + subdir)
        print(str(index) + ": " + subdir)
        index = index + 1 
        
userInput = int(input("Which project? [0, " + str(len(listSubDirPath)-1) + "] "))
        
if userInput > len(listSubDirPath) - 1 or userInput < 0:
    userInput = int(input("Input out of range. Try again. [0, " + str(len(listSubDirPath)-1) + "] "))

subDirPath = listSubDirPath[userInput]


#gather all required libs in .h and .cpp in target folder
targetLib = subDirPath[subDirPath.rfind('/')+1:-2]
print("\nRequired libs by " + targetLib + ":")

fctSearchForLibsInFile(subDirPath + '/' + targetLib + '.h')

fctSearchForLibsInFile(subDirPath + '/' + targetLib + '.cpp')

if (listOfRequiredLibs == []):
    print("\tNo libs found")
else: #some libs found
    libDirTarget = subDirPath + "/lib"
    if not(os.path.isdir(libDirTarget)):
        os.mkdir(libDirTarget)
    else:#loop through lib folder, search for further required libs and check if available libs are up to date
        for fileName in os.listdir(libDirTarget):
            filePath = libDirTarget + "/" + fileName
            if os.path.isfile(filePath):
                if filePath[-2:] == ".h" or filePath[-4:] == ".cpp":
                    fctSearchForLibsInFile(filePath)
                if filePath[-4:] == ".cpp":
                    currentLibName = filePath[filePath.rfind('/')+1:-4]
                    currentLibVersion = getLibVersion(filePath)
                    popIndex = -1
                    for index, lib in enumerate(listOfRequiredLibs):
                        if currentLibName == lib[0]:
                            popIndex = index
                            processedLibs.append(lib)
                            if currentLibVersion != lib[1]:
                                if currentLibVersion == "-1.-1":
                                    errorMessages.append("Lib " + currentLibName + " in ./lib has no version tag in .cpp. Update header and source of lib manually.")
                                    #print("Lib " + currentLibName + " in ./lib has no version tag in .cpp. Update header and source of lib manually.")
                                else:
                                    errorMessages.append("Wrong version of " + currentLibName + " found in ./lib: v" + currentLibVersion + ". Expected: v" + lib[1])
                                    #print("Wrong version of " + currentLibName + " found in ./lib: v" + currentLibVersion + ". Expected: v" + lib[1])
                                break
                    if popIndex != -1:
                        listOfRequiredLibs.pop(popIndex)
                        
#loop through required libs and check, if version is defined correctly
popIndex = []
for index, lib in enumerate(listOfRequiredLibs):
    if lib[1] == "Nan":
        errorMessages.append("Wrong format of version of " + lib[0] + " v" + lib[1] + ". Update version after #include")
        #print("Wrong format of version of " + lib[0] + " v" + lib[1] + ". Update version after #include")
        popIndex.append(index)
        processedLibs.append(lib)

for index in range(0,len(popIndex)):
    listOfRequiredLibs.pop(popIndex[-index-1])

#copy missing libs                    
popIndex = []
for index, lib in enumerate(listOfRequiredLibs):
    folder = workingDirectory + "/" + lib[0] + ".X"
    if os.path.isdir(folder):
        source = folder + "/" + lib[0] + ".cpp"
        version = getLibVersion(source)
        if not(version == lib[1]):
            errorMessages.append("Version missmatch of " + lib[0] + ". Required v" + lib[1] + ". Found v" + version)
            popIndex.append(index)
            processedLibs.append(lib)
        else:
            shutil.copy(source, libDirTarget)
            header = source[:-4] + ".h"
            shutil.copy(header, libDirTarget)
    else:
        errorMessages.append("No project found for " + lib[0])
        popIndex.append(index)
        processedLibs.append(lib)
            
for index in range(0,len(popIndex)):
    listOfRequiredLibs.pop(popIndex[-index-1])

#print error Messages
if errorMessages != []:
    print("\nErrors")
    for msg in errorMessages:
        print("\t"+msg)

                


