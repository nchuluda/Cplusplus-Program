#include <iostream>
#include <fstream>
#include <vector>
#include <jni.h>
using namespace std;

void GenerateData()               //DO NOT TOUCH CODE IN THIS METHOD
{
     JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
     JNIEnv *env;                      // Pointer to native interface
                                                              //================== prepare loading of Java VM ============================
     JavaVMInitArgs vm_args;                        // Initialization arguments
     JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
     options[0].optionString = (char*) "-Djava.class.path=";   // where to find java .class
     vm_args.version = JNI_VERSION_1_6;             // minimum Java version
     vm_args.nOptions = 1;                          // number of options
     vm_args.options = options;
     vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
                                                                          //=============== load and initialize Java VM and JNI interface =============
     jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
     delete options;    // we then no longer need the initialisation options.
     if (rc != JNI_OK) {
            // TO DO: error processing...
            cin.get();
            exit(EXIT_FAILURE);
     }
     //=============== Display JVM version =======================================
     cout << "JVM load succeeded: Version ";
     jint ver = env->GetVersion();
     cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

     jclass cls2 = env->FindClass("ZooFileWriter");  // try to find the class
     if (cls2 == nullptr) {
            cerr << "ERROR: class not found !";
     }
     else {                                  // if class found, continue
            cout << "Class MyTest found" << endl;
            jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V");  // find method
            if (mid == nullptr)
                   cerr << "ERROR: method void createZooFile() not found !" << endl;
            else {
                   env->CallStaticVoidMethod(cls2, mid);                      // call method
                   cout << endl;
            }
     }


     jvm->DestroyJavaVM();
     cin.get();
}

class Animal {
	public:
		string trackNum = "NoNum";
		string name = "NoName";
		string type = "NoType";
		string subType = "NoSubType";
		string numberOfEggs = "NoEggs";
		string nurse = "NoNurse";

		void SetName(string t_name)
			{ name = t_name; };
		void SetTrackNum(string t_trackNum)
			{ trackNum = t_trackNum; };
		void SetType(string t_type)
			{ type = t_type; };
		void SetSubType(string t_subType)
			{ subType = t_subType; };
		void SetNumberOfEggs(string t_numberOfEggs)
			{ numberOfEggs = t_numberOfEggs; };
		void SetNurse(string t_nurse)
			{ nurse = t_nurse; };
		string GetName() const
			{ return name; };
		string GetTrackNum() const
			{ return trackNum; };
		string GetType() const
			{ return type; };
		string GetSubType() const
			{ return subType; };
		string GetNumberOfEggs() const
			{ return numberOfEggs; };
		string GetNurse() const
			{ return nurse; };
};

class Oviparous : public Animal {
	public:
		void Print();
};

void Oviparous::Print() {
	cout << "Track Number: " << trackNum << endl;
	cout << "Name: " << name << endl;
	cout << "Type: " << type << endl;
	cout << "SubType: " << subType << endl;
	cout << "Number of eggs: " << numberOfEggs << endl << endl;
}

class Mammal : public Animal {
	public:
		void Print();
};

void Mammal::Print() {
	cout << "Track Number: " << trackNum << endl;
	cout << "Name: " << name << endl;
	cout << "Type: " << type << endl;
	cout << "SubType: " << subType << endl;
	cout << "Nursing: " << nurse << endl << endl;
}
class Crocodile : public Oviparous {
};

class Goose : public Oviparous {
};

class Pelican : public Oviparous {
};

class Bat : public Mammal {
};

class Whale : public Mammal {
};

class SeaLion : public Mammal {
};

vector<Animal> animalList;

string padLeft(string str, int leng, string stringpadVal) {
    for (int i = str.length(); i < leng; i++)
    str = stringpadVal + str;
    return str;
}

string padRight(string str, int leng, string stringpadVal) {
    for (int i = str.length(); i < leng; i++)
    str = str + stringpadVal;
    return str;
}

void AddAnimal()
{
	 string trackNumber = "";
	 string animalName = "";
	 string animalType = "";
	 string animalSubType = "";
	 string numEggs = "";
	 string doesNurse = "";

     cout << "To add a record, please enter the following:" << endl;

     cout << "Track #: ";

     while (trackNumber.length() != 6) {
    	 cin >> trackNumber;
    	 if (trackNumber.length() != 6) {
    		 cout << "Error: Track # must be 6 digits. Please try again." << endl;
    	 }
     }

     trackNumber = padRight(trackNumber, 7, " ");
     trackNumber = padLeft(trackNumber, 8, "0");

     cout << "Name: ";
     cin >> animalName;
     while (animalName.length() > 15) {
    	 cout << "Error: Name must not me more than 15 characters. Please try again." << endl;
    	 cin >> animalName;
     }

     animalName = padRight(animalName, 17, " ");

     cout << "Type: ";

     while (animalType != "Oviparous" && animalType != "Mammal") {
    	 cin >> animalType;
    	 if (animalType != "Oviparous" && animalType != "Mammal") {
    		 cout << "Error: Please enter Oviparous or Mammal." << endl;
    	 }
     }

     animalType = padRight(animalType, 17, " ");

     cout << "Sub-type: ";

     while (animalSubType != "Crocodile" && animalSubType != "Goose" && animalSubType != "Pelican"
    		 && animalSubType != "Bat" && animalSubType != "Whale" && animalSubType != "SeaLion") {
    	 cin >> animalSubType;
    	 if (animalSubType != "Crocodile" && animalSubType != "Goose" && animalSubType != "Pelican"
        		 && animalSubType != "Bat" && animalSubType != "Whale" && animalSubType != "SeaLion") {
    		 cout << "Error: Please enter Crocodile / Goose / Pelican / Bat / Whale / SeaLion" << endl;
    	 }
     }

     animalSubType = padRight(animalSubType, 17, " ");

     cout << "Number of eggs: ";

     cin >> numEggs;

     numEggs = padRight(numEggs, numEggs.length() + 1, " ");

     cout << "Nursing? 0 = No, 1 = Yes: ";

     while (doesNurse != "0" && doesNurse != "1") {
    	 cin >> doesNurse;
    	 if (doesNurse != "0" && doesNurse != "1") {
    		 cout << "Error: Please enter 0 or 1." << endl;
    	 }
     }

     if (animalSubType == "Crocodile" || animalSubType == "crocodile") {
     		     	 Crocodile newCrocodile;
     		     	 newCrocodile.SetTrackNum(trackNumber);
     		     	 newCrocodile.SetName(animalName);
     		     	 newCrocodile.SetNumberOfEggs(numEggs);

     		     	 animalList.push_back(newCrocodile);
     		 }

     		 if (animalSubType == "Goose" || animalSubType == "goose") {
     		 		 Goose newGoose;
     		 		 newGoose.SetTrackNum(trackNumber);
     		 		 newGoose.SetName(animalName);
     		 		 newGoose.SetNumberOfEggs(numEggs);

     		 		 animalList.push_back(newGoose);
     		 }

     		 if (animalSubType == "Pelican" || animalSubType == "pelican") {
     		 		  Pelican newPelican;
     		 		  newPelican.SetTrackNum(trackNumber);
     		 		  newPelican.SetName(animalName);
     		 		  newPelican.SetNumberOfEggs(numEggs);

     		 		  animalList.push_back(newPelican);
     		 }

     		 if (animalSubType == "Bat" || animalSubType == "bat") {
     		 		  Bat newBat;
     		 		  newBat.SetTrackNum(trackNumber);
     		 		  newBat.SetName(animalName);
     		 		  newBat.SetNurse(doesNurse);

     		 		  animalList.push_back(newBat);
     		 }

     		 if (animalSubType == "Whale" || animalSubType == "whale") {
     		 		  Whale newWhale;
     		 		  newWhale.SetTrackNum(trackNumber);
     		 		  newWhale.SetName(animalName);
     		 		  newWhale.SetNurse(doesNurse);

     		 		  animalList.push_back(newWhale);
     		 }

     		 if (animalSubType == "SeaLion" || animalSubType == "sealion") {
     		 		  SeaLion newSeaLion;
     		 		  newSeaLion.SetTrackNum(trackNumber);
     		 		  newSeaLion.SetName(animalName);
     		 		  newSeaLion.SetNurse(doesNurse);

     		 		  animalList.push_back(newSeaLion);
     		 }

     cout << "Added to list:" << endl;
     cout << trackNumber << animalName << animalType << animalSubType << numEggs << doesNurse << endl;
}


void RemoveAnimal()
{
     string removeTrackNum;

     cout << "Enter track number to delete: ";

     cin >> removeTrackNum;
}

void LoadDataFromFile()
{
      //TODO: Write proper code to load data from input file (generated using JNI) into vector/array.

	 string trackNumber;
	 string animalName;
	 string animalType;
	 string animalSubType;
	 string numEggs;
	 string doesNurse;

     ifstream inFS;
     cout << "Opening file zoodata.txt." << endl;

     inFS.open("zoodata.txt");
     if(!inFS.is_open()) {
    	 cout << "Could not open zoodata.txt." << endl;
     }

     cout << "Reading file." << endl << endl;

     while (!inFS.eof()) {
		 inFS >> trackNumber;
		 inFS >> animalName;
		 inFS >> animalType;
		 inFS >> animalSubType;
		 inFS >> numEggs;
		 inFS >> doesNurse;

		 animalName = padRight(animalName, 15, " ");

		 if (animalSubType == "Crocodile" || animalSubType == "crocodile") {
		     	 Crocodile newCrocodile;
		     	 newCrocodile.SetTrackNum(trackNumber);
		     	 newCrocodile.SetName(animalName);
		     	 newCrocodile.SetType("Oviparous        ");
		     	 newCrocodile.SetSubType("Crocodile        ");
		     	 newCrocodile.SetNumberOfEggs(numEggs);
		     	 newCrocodile.SetNurse(doesNurse);
		     	 newCrocodile.Print();
		     	 animalList.push_back(newCrocodile);
		 }

		 if (animalSubType == "Goose" || animalSubType == "goose") {
		 		 Goose newGoose;
		 		 newGoose.SetTrackNum(trackNumber);
		 		 newGoose.SetName(animalName);
		 		 newGoose.SetType("Oviparous        ");
		 		 newGoose.SetSubType("Goose            ");
		 		 newGoose.SetNumberOfEggs(numEggs);
		 		 newGoose.SetNurse(doesNurse);
		 		 newGoose.Print();
		 		 animalList.push_back(newGoose);
		 }

		 if (animalSubType == "Pelican" || animalSubType == "pelican") {
		 		  Pelican newPelican;
		 		  newPelican.SetTrackNum(trackNumber);
		 		  newPelican.SetName(animalName);
		 		  newPelican.SetType("Oviparous        ");
		 		  newPelican.SetSubType("Pelican          ");
		 		  newPelican.SetNumberOfEggs(numEggs);
		 		  newPelican.SetNurse(doesNurse);
		 		  newPelican.Print();
		 		  animalList.push_back(newPelican);
		 }

		 if (animalSubType == "Bat" || animalSubType == "bat") {
		 		  Bat newBat;
		 		  newBat.SetTrackNum(trackNumber);
		 		  newBat.SetName(animalName);
		 		  newBat.SetType("Mammal           ");
		 		  newBat.SetSubType("Bat              ");
		 		  newBat.SetNumberOfEggs(numEggs);
		 		  newBat.SetNurse(doesNurse);
		 		  newBat.Print();
		 		  animalList.push_back(newBat);
		 }

		 if (animalSubType == "Whale" || animalSubType == "whale") {
		 		  Whale newWhale;
		 		  newWhale.SetTrackNum(trackNumber);
		 		  newWhale.SetName(animalName);
		 		  newWhale.SetType("Mammal           ");
		 		  newWhale.SetSubType("Whale            ");
		 		  newWhale.SetNumberOfEggs(numEggs);
		 		  newWhale.SetNurse(doesNurse);
		 		  newWhale.Print();
		 		  animalList.push_back(newWhale);
		 }

		 if (animalSubType == "SeaLion" || animalSubType == "sealion") {
		 		  SeaLion newSeaLion;
		 		  newSeaLion.SetTrackNum(trackNumber);
		 		  newSeaLion.SetName(animalName);
			      newSeaLion.SetType("Mammal           ");
			      newSeaLion.SetSubType("SeaLion          ");
			      newSeaLion.SetNumberOfEggs(numEggs);
		 		  newSeaLion.SetNurse(doesNurse);
		 		  newSeaLion.Print();
		 		  animalList.push_back(newSeaLion);
		 }
     }

     cout << "Load complete." << endl;
     inFS.close();

}

void SaveDataToFile()
{
	ofstream outFS("zoodata.txt");

	for (int i = 0; animalList.size(); ++i) {
		//FIXME OUTPUT EACH ANIMAL
	}
}

void DisplayList()
{
	cout << "Track#  Name            Type              SubType        Eggs    Nursing" << endl;
	cout << "------------------------------------------------------------------------" << endl;
	for (Animal anml : animalList) {
		cout << anml.GetTrackNum() << " " << anml.GetName() << " " << anml.GetType() << " " << anml.GetSubType() << " " << anml.GetNumberOfEggs() << "    " << anml.GetNurse() << endl ;
	}
	cout << "------------------------------------------------------------------------" << endl;
	cout << endl;
}

void DisplayMenu()
{
     int selection = 0;

     do {
    	 cout << " Menu: " << endl;
    	 cout << "===========================" << endl;
    	 cout << " 1. Load Animal Data" << endl;
    	 cout << " 2. Generate Data" << endl;
    	 cout << " 3. Display Animal Data" << endl;
    	 cout << " 4. Add Record" << endl;
    	 cout << " 5. Delete Record" << endl;
    	 cout << " 6. Save Animal Data" << endl;
    	 cout << " 7. Exit" << endl;
    	 cout << "===========================" << endl;
    	 cout << " Please enter a selection:" ;

    	 cin >> selection;

    	 cout << endl;

    	 switch (selection)
    	 {
    	 case 1:
    		 LoadDataFromFile();
    		 break;

    	 case 2:
    		 GenerateData();
    		 break;

    	 case 3:
    		 DisplayList();
    		 break;

    	 case 4:
    		 AddAnimal();
    		 break;

    	 case 5:
    		 cout << "5" << endl;
    		 break;

    	 case 6:
    		 cout << "6" << endl;
    		 break;

    	 case 7:
    		 cout << "Goodbye." << endl;
    		 break;

    	 default:
    		 cout << selection << " is not a valid menu item." << endl;
    	 }

     }
     while (selection != 7);
}



int main()
{
	//GenerateData();
	DisplayMenu();
	return 1;
}
