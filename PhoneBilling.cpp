//-----------------------------------------------------------------------------------------------
//headers
//-----------------------------------------------------------------------------------------------

#include<iostream>
#include<string>
#include<stdlib.h>
#include<vector>
#include<stdio.h>
#include<conio.h>
#include<ctime>
#include<fstream>
#include <windows.h>

using namespace std;



//-----------------------------------------------------------------------------------------------
//abstract class
//-----------------------------------------------------------------------------------------------

class Abstract
{
public:
	virtual double getCost() = 0; //pure virtual function
};



//-----------------------------------------------------------------------------------------------
//1st class: PhoneCall
//-----------------------------------------------------------------------------------------------

class PhoneCall : public Abstract
{
private:
	string PersonName;
    string PhoneNumber;
    string StartDateTime;
    int CallDuration;
    double PerSecondCallCost;
public:
    PhoneCall() //constructor
    {
        PhoneNumber = "";
        StartDateTime = "";
        CallDuration = 0;
        PerSecondCallCost = 0;
    }
    ~PhoneCall() //destructor
    {

    }
	void setPersonName(string name) //set a name of receiver
	{
		PersonName = name;
	}
    void setPhoneNumber(string phnNumber) //set a phone number to call
    {
        PhoneNumber = phnNumber;
    }
    void setStartDateTime(string DateTime) //set current date & time
    {
        StartDateTime = DateTime;
    }
    void setCallDuration(int seconds) //set call duration of a call
    {
        CallDuration = seconds;
    }
    void setPerSecondCallCost(float cost) //set per second call cost
    {
        PerSecondCallCost = cost;
    }
	string getPersonName() //get name of receiver
	{
		return PersonName;
	}
    string getPhoneNumber() //get phone number of receiver
    {
        return PhoneNumber;
    }
    string getStartDateTime() //get current date & time
    {
        return StartDateTime;
    }
    int getCallDuration() //get call duration of a call
    {
        return CallDuration;
    }
    double getPerSecondCallCost() // get per second call cost
    {
        return PerSecondCallCost;
    }
    double getCost() //payable cost of a call
    {
        return PerSecondCallCost*CallDuration;
    }
};


//------------------------------------------------------------------------------------------------
// Inherit the PhoneCall class
//------------------------------------------------------------------------------------------------

class Message : public PhoneCall
{
private:
	string message;
	double PerMessageCost;
public:
	Message() //constructor
	{
		message = "" ;
		PerMessageCost = 0;
	}
	~Message() //destructor
	{

	}
	void setMessage(string msg) //set message
	{
		message = msg;
	}
	string getMessage() //get message
	{
		return message;
	}
	double getCost() //message cost
	{
		double cost=0;

		if(message.length()>0 && message.length()<=150)
		{
			cost = 1.15;
			return cost;
		}
		else if(message.length()>150 && message.length()<=300)
		{
			cost = 2.30;
			return cost;
		}
		else if(message.length()>300 && message.length()<=450)
		{
			cost = 3.45;
			return cost;
		}
		else if(message.length()>450 && message.length()<=600)
		{
			cost = 4.60;
			return cost;
		}
	}
};


//------------------------------------------------------------------------------------------------
// PhoneBook Class
//------------------------------------------------------------------------------------------------

class PhoneBook : public PhoneCall
{
private:
	string PersonNumber;
public:
    PhoneBook() //constructor
    {
		PersonNumber = "";
    }
	~PhoneBook()
    {

    }
	void setPersonNumber(string num) //set contact person phone number
	{
		PersonNumber = num;
	}
	string getPersonNumber() //get contact person's phone number
	{
		return PersonNumber;
	}
};



//------------------------------------------------------------------------------------------------
//2nd class: Phone
//------------------------------------------------------------------------------------------------

class Phone
{
private:
    string phnNumber;
    float Credit;
public:
	vector<Message> Mssg;
	vector<PhoneBook> Contact;
	vector<PhoneCall> CallLog;

    Phone() //constructor
    {
		phnNumber = "";
        Credit=100; //initialized credit as 100
    }
    ~Phone() //destructor
    {

    }
    void setPhnNumber(string number) //set a number of a Phone of a person
    {
        phnNumber = number;
    }
    void setCredit(int balance) //set credit of a phone
    {
        Credit += balance; //add credit
    }
    void AddCall(PhoneCall call) //taking a object of PhoneCall class
    {
        CallLog.push_back(call); //enter a object of PhoneCall class in CallLog
        Credit -= call.getCost(); //present credit calculation
    }
	void AddMessage(Message msg)  //taking a object of Message class
	{
		Mssg.push_back(msg); //enter a object of Message class in Message History
		Credit -= msg.getCost(); //present credit calculation
	}
	void AddContact(PhoneBook phnBook) //taking a object of PhoneBook class
	{
		Contact.push_back(phnBook);//enter a object of PhoneBook class in Contact
	}
    string getPhnNumber() //get number of a Phone of a person
    {
        return phnNumber;
    }
    float getCredit() //get present credit
    {
        return Credit;
    }
    vector<PhoneCall> getCallHistory() //get a call history of a call
    {
        return CallLog;
    }
	vector<Message> getMessageHistory() //get a message history of a call
    {
        return Mssg;
    }
	vector<PhoneBook> getContactsList() //get a contact list of a phone
    {
        return Contact;
    }
};



//------------------------------------------------------------------------------------------------
//3rd class: Person
//------------------------------------------------------------------------------------------------

class Person
{
public:
	vector<Phone> registerPhone;
};



//------------------------------------------------------------------------------------------------
//others function
//------------------------------------------------------------------------------------------------

//http://stackoverflow.com/questions/17335816/clear-screen-using-c
void clrscr() //to clear screen
{
   system("cls");
}


//http://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
string Time() //to set present time & date
{
    time_t now = time(0);
    char* DateTime = ctime(&now);

    return DateTime;
}


void TimeConvert(int s) //convert to minute
{
	int minute,second=s;

	if( second > 60)
	{
		minute = second /60; //find minute
		second = second % 60; //find second
		cout << minute << "min " << second << "sec" << endl; //print minute & second
	}
	else
	{
	       cout << second << "sec" << endl; //print only second
	}
}


bool isNumber(string str) //check string(integer or character)
{
	bool result = true;

	for(int i=0;i<str.length();i++)
	{
		if(!(str[i]<=57 && str[i]>=48)) //check string(integer)
		{
			result = false;
			break;
		}
	}
	return result;
}


int CallClock(int dMax) //call duration clock && counter
{
	int duration=0;
	int sec=0;
	int min=0;
	int hour=0;

	bool press = true;

	while(press)
    {
        clrscr();

		cout<<"\ncalling...\n";
		cout << "\n" << hour << " : " << min << " : " << sec << endl; //show CallClock
		cout << "\nPress 'End Key' To End The Call." << endl; //show end warning

		//http://stackoverflow.com/questions/4184468/sleep-for-milliseconds
		Sleep(500); //hold half second

        sec += 1; //increase second
        duration++; //increase duration

		if(duration>dMax)
		{
			break;
		}

        if(sec==60) //convert second to minute
        {
            sec=0;
            min += 1; //increase minute

			if(min==60) //convert minute to hour
            {
                min=0;
                hour += 1; //increase hour
            }
        }

		//http://stackoverflow.com/questions/15737495/c-execute-a-while-loop-until-a-key-is-pressed-e-g-esc
		if (GetAsyncKeyState(VK_END)) //break the loop
        {
            press=false;
        }
    }

	return duration; //return the duration
}


void allWork()
{
	Person p; //Person class object declare

	string name; //for name
	string msg; //for message
    string PhnNum; //for phone number
	int checker=0; //option selector
	int check=0; //option selector
    int select = 0; //option selector
    int second = 0; //count minute & second


    cout << "\tREGISTER MENU\n" << "\n1.Register\n" << "2.Registered Phone\n" << "3.All Phones Options" << endl;
	cout << "\nPress 100 to Quit." << endl;

	while(1)
    {
        cout << "\n\nGo To: ";
        cin >> select;

		if(select==0) //register menu
        {
            clrscr(); //clear screen

            cout << "\tREGISTER MENU\n" << "\n1.Register\n" << "2.Registered Phone\n" << "3.All Phones Options" << endl;
			cout << "\nPress 100 to Quit." << endl;
        }
        else if(select==1) //register a phone
        {
            clrscr();

			cout << "\tREGISTER" << endl;
            cout << "\nRegister A Phone by Number : ";
            cin >> PhnNum;

			if(PhnNum.length()>=8 && PhnNum.length()<=11) //check string length
			{
				try //exeption handling
				{
					if(isNumber(PhnNum)) //check string
					{
						for(int i=0;i<p.registerPhone.size();i++)
						{
							check=0;

							if(PhnNum.compare(p.registerPhone[i].getPhnNumber())==0) //check others register number
							{
								check=1;
								break;
							}
						}
						if(check==0)
						{
							Phone temp; //Phone class object declare

							temp.setPhnNumber(PhnNum); //set phone number of a person
							p.registerPhone.push_back(temp); //enter a object in Person class

							cout << "\nRegistration Successful." << endl;

							Sleep(1000); //hold 1 second

							clrscr(); //clear screen

							cout << "\tREGISTER MENU\n" << "\n1.Register\n" << "2.Registered Phone\n" << "3.All Phones Options" << endl;
							cout << "\nPress 100 to Quit" << endl;
						}
						else
						{
							clrscr(); //clear screen

							cout << "\tREGISTER PHONE" << endl;
							cout << "\nThis Number Is Already Registered." << endl;
							cout << "\n\nPress 0 to go to Register Menu." << endl;
						}
					}
					else
					{
						throw "Invalid Number.";
					}
				}

				catch(char* msg)
				{
					clrscr(); //clear screen

					cout << "\tREGISTER PHONE" << endl;
					cout << "\n" << msg << endl;
					cout << "\n\nPress 0 to go to Register Menu." << endl;
				}
			}
			else
			{
				clrscr(); //clear screen

				cout << "\tREGISTER PHONE" << endl;
				cout << "\nInvalid Number." << endl;
				cout << "\n\nPress 0 to go to Register Menu." << endl;
			}
        }
        else if(select==2) //registered phone list
        {
            clrscr(); //clear screen

			cout << "\tREGISTERED PHONE LIST\n" << endl;

			for(int i=0;i<p.registerPhone.size();i++)
            {
				cout << i+1 << ". " << p.registerPhone[i].getPhnNumber() << endl; //show registered phone number
            }

            if(p.registerPhone.size()>0)
			{
				int num;

				cout << "\n\nSelect A Phone by Serial Number,Otherwise Press 0." << endl;
				cout << "Select : ";
				cin >> num;

				if(num>0 && num<p.registerPhone.size()+1) //choose a registered number
				{
				    clrscr(); //clear screen

					cout << "\tPHONE MENU\n" << "\n1.Call\n" << "2.Message\n" << "3.PhoneBook\n" << "4.Credit\n" << "5.Call History" << endl;
					cout << "\nPress 100 to go to Register Menu." <<endl;

				    while(1)
				    {
				        cout << "\n\nGo To: ";
				        cin >> select;

				        if(select==0) // Phone menu option
				        {
				            clrscr(); //clear screen

				            cout << "\tPHONE MENU\n" << "\n1.Call\n" << "2.Message\n" << "3.PhoneBook\n" << "4.Credit\n" << "5.Call History" << endl;
							cout << "\nPress 100 to go to Register Menu." <<endl;

				        }
						else if(select==1) //call option
				        {
				            clrscr(); //clear screen

							cout << "\tCALL" << endl;
				            cout << "\n11.By Number\n12.From Contacts List" << endl;
				            cout << "\nPress 0 to go to Phone Menu." << endl;
				        }
				        else if(select==11) //call by number option
				        {
				            clrscr(); //clear screen

							if( p.registerPhone[num-1].getCredit() < 1) //check credit to make call
							{
				                    cout << "\nPlease Recharge First." << endl;
									cout << "\n\nPress 4 to go to Credit Option." << endl;
									cout << "Press 1 to go to Call Option." << endl;
									cout << "Press 0 to go to Phone Menu." << endl;
							}
				            else
				                {
				                    cout << "\tCALL" << endl;
				                    cout << "\nEnter Phone Number: ";
				                    cin >> PhnNum;
									cout<<"\nconnecting...\n";
									Sleep(1000);

									if(PhnNum.compare(p.registerPhone[num-1].getPhnNumber())!=0) //check register number
									{
										if(PhnNum.length()>=8 && PhnNum.length()<=16) //check phone number length
										{
											if(isNumber(PhnNum)) //check string
											{
												int loop;
												double creditCheck = p.registerPhone[num-1].getCredit(); //check credit

												int durationMax = creditCheck/0.02 - 1; //check max duration

												int duration = CallClock(durationMax); //show CallClock

												cout<<"\ncall end...\n";
												Sleep(1000); //hold 1 second

												PhoneCall tempCall; //PhoneCall class object declare

												for(loop=0;loop<p.registerPhone[num-1].Contact.size();loop++) //for all contact number
												{
													if(PhnNum.compare(p.registerPhone[num-1].Contact[loop].getPersonNumber())==0) //check contact phone number
													{
														checker = 1;
														break;
													}
												}

												if(checker==1)
												{
													tempCall.setPersonName(p.registerPhone[num-1].Contact[loop].getPersonName()); //set contact name for call history
												}
												else
												{
													tempCall.setPersonName("Unknown");
												}

												tempCall.setPhoneNumber(PhnNum); //send phone number
												tempCall.setStartDateTime(Time()); //send present time& date

												if(duration<2)
												{
													tempCall.setCallDuration(0);
													tempCall.setPerSecondCallCost(0);
												}
												else
												{
													tempCall.setCallDuration(duration); //send call duration
													tempCall.setPerSecondCallCost(0.02); //fix per second call cost
												}

												p.registerPhone[num-1].AddCall(tempCall); //send an object

												//for save call history a text file
												ofstream outfile;
												outfile.open("callhistory.txt",ios_base::app);

												outfile << "Name: " << tempCall.getPersonName() << endl;
												outfile << "PhoneNumber: " << tempCall.getPhoneNumber() << endl;
												outfile << "Time & Date: " << tempCall.getStartDateTime();
												outfile << "Call Duration: " << tempCall.getCallDuration() <<endl;
												outfile << "Call Cost: " << tempCall.getCost() << "\n\n" << endl;

												outfile.close();

												clrscr(); //clear screen

												cout << "\tCALL" << endl;
												cout << "\n11.By Number\n12.From Contacts List" << endl;
												cout << "\nPress 0 to go to Phone Menu." << endl;
											}
											else
											{
												clrscr(); //clear screen

												cout << "\tCALL" << endl;
												cout << "\nInvalid Number." << endl;
												cout << "\n\nPress 1 to go to Call Option." << endl;
												cout << "Press 0 to go to Phone Menu." << endl;
											}
										}
										else
										{
											clrscr(); //clear screen

											cout << "\tCALL" << endl;
											cout << "\nInvalid Number." << endl;
											cout << "\n\nPress 1 to go to Call Option." << endl;
											cout << "Press 0 to go to Phone Menu." << endl;
										}
									}
									else
									{
										clrscr(); //clear screen

										cout << "\tCALL" << endl;
										cout << "\nThis Is Your Registration Number.Choose Another Number To Call." << endl;
										cout << "\n\nPress 1 to go to Call Option." << endl;
										cout << "Press 0 to go to Phone Menu." << endl;
									}
				                }
				        }
						else if(select==12) //call from contact list
						{
							clrscr(); //clear screen

				            cout << "\tCONTACTS LIST" << endl;

							vector<PhoneBook> contacts = p.registerPhone[num-1].getContactsList(); //for all contact list

				            for(int j=0 ; j<contacts.size() ; j++)
				            {
								cout << "\n" << j+1 << "." << endl; //show number
								cout << "Name : " << contacts[j].getPersonName() << endl; //show contact name
				                cout << "Phone Number : " << contacts[j].getPersonNumber() << endl; //show contact number
				            }

							if(p.registerPhone[num-1].Contact.size()>0) //select one contact number to call
							{
								int chooser;

								cout << "\n\nSelect A contact by Serial Number To Call,Otherwise Press 0." << endl;
								cout << "Select : ";
								cin >> chooser;

								if(chooser>0 && chooser<p.registerPhone[num-1].Contact.size()+1) //select one contact number to call
								{
									clrscr(); //clear screen

								 	if( p.registerPhone[num-1].getCredit() < 1) //check credit to make call
									{
									        cout << "\nPlease Recharge First." << endl;
											cout << "\n\nPress 4 to go to Credit Option." << endl;
											cout << "Press 1 to go to Call Option." << endl;
											cout << "Press 0 to go to Phone Menu." << endl;
									}
									else
									{
									    cout << "\tCALL" << endl;

										PhnNum = p.registerPhone[num-1].Contact[chooser-1].getPersonNumber(); //take contact phone number

										cout<<"\nconnecting...\n";
										Sleep(1000); //hold 1 second

										if(PhnNum.compare(p.registerPhone[num-1].getPhnNumber())!=0) //check registered number
										{
											if(PhnNum.length()>=8 && PhnNum.length()<=16) //check phone number length
											{
												if(isNumber(PhnNum)) //check string
												{
													double creditCheck = p.registerPhone[num-1].getCredit(); //check credit

													int durationMax = creditCheck/0.02 - 1; //check max duration

													int duration = CallClock(durationMax); //show CallClock

													cout<<"\ncall end...\n";
													Sleep(1000); //hold 1 second

													PhoneCall tempCall; //declare PhoneCall class object

													tempCall.setPersonName(p.registerPhone[num-1].Contact[chooser-1].getPersonName()); //send contact person name
													tempCall.setPhoneNumber(PhnNum); //send phone number
													tempCall.setStartDateTime(Time()); //send present time& date

													if(duration<2) //for miss call option
													{
														tempCall.setCallDuration(0); //set call duration as 0
														tempCall.setPerSecondCallCost(0); //set call cost as 0
													}
													else
													{
														tempCall.setCallDuration(duration); //send call duration
														tempCall.setPerSecondCallCost(0.02); //fix per second call cost
													}

													p.registerPhone[num-1].AddCall(tempCall); //send an object

													//for save call history a text file
													ofstream outfile;
													outfile.open("callhistory.txt",ios_base::app);

													outfile << "Name: " << tempCall.getPersonName() << endl;
													outfile << "PhoneNumber: " << tempCall.getPhoneNumber() << endl;
													outfile << "Time & Date: " << tempCall.getStartDateTime();
													outfile << "Call Duration: " << tempCall.getCallDuration() <<endl;
													outfile << "Call Cost: " << tempCall.getCost() << "\n\n" << endl;

													outfile.close();

													clrscr(); //clear screen

													cout << "\tCALL" << endl;
													cout << "\n11.By Number\n12.From Contacts List" << endl;
													cout << "\nPress 0 to go to Phone Menu." << endl;
												}
												else
												{
													clrscr(); //clear screen

													cout << "\tCALL" << endl;
													cout << "\nInvalid Number." << endl;
													cout << "\n\nPress 1 to go to Call Option." << endl;
													cout << "Press 0 to go to Phone Menu." << endl;
												}
											}
											else
											{
												clrscr(); //clear screen

												cout << "\tCALL" << endl;
												cout << "\nInvalid Number." << endl;
												cout << "\n\nPress 1 to go to Call Option." << endl;
												cout << "Press 0 to go to Phone Menu." << endl;
											}
										}
										else
										{
											clrscr(); //clear screen

											cout << "\tCALL" << endl;
											cout << "\nThis Is Your Registration Number.Choose Another Number To Call." << endl;
											cout << "\n\nPress 1 to go to Call Option." << endl;
											cout << "Press 0 to go to Phone Menu." << endl;
										}
									}
								}
								else if(chooser==0)
								{
									clrscr(); //clear screen

									cout << "\tCALL" << endl;
									cout << "\tPHONEBOOK" << endl;
									cout << "\n31.Add Contact" << "\n32.Contacts List"  << endl;
									cout << "\nPress 0 to go to Phone Menu." << endl;
								}
								else
								{
									clrscr(); //clear screen

									cout << "\tCALL" << endl;
									cout << "\nSerial Number Did Not Match." << endl;
									cout << "\n\nPress 1 to go to Call Option." << endl;
									cout << "Press 0 to go to Phone Menu." << endl;
								}
							}
							else
							{
								clrscr(); //clear screen

								cout << "\tCALL" << endl;
								cout << "\nNo Contact Number." << endl;
								cout << "\n\nPress 3 to go to PhoneBook Option." << endl;
								cout << "Press 0 to go to Phone Menu." << endl;
							}
						}
						else if(select==2) //message option
				        {
				            clrscr(); //clear screen

							cout << "\tMESSAGE" << endl;
				            cout << "\n21.Send Message" << "\n22.Message History" << "\n23.Delete All History" << endl;
				            cout << "\nPress 0 to go to Phone Menu." << endl;
				        }
						else if(select==21) //send message option
				        {
				            clrscr(); //clear screen

							if( p.registerPhone[num-1].getCredit() < 5) //check credit
							{
								cout << "\nPlease Recharge First." << endl;
								cout << "\n\nPress 4 to go to Credit Option." << endl;
								cout << "Press 2 to go to Message Option." << endl;
								cout << "Press 0 to go to Phone Menu." << endl;
							}
				            else
				            {
				                cout << "\tSEND MESSAGE" << endl;

								cout << "\nEnter Your Message : " <<endl;

								cin.ignore();
								getline(cin,msg); //write message
								cin.clear();

								if(msg.size()>600)
								{
									clrscr(); //clear screen

									cout << "\tMESSAGE" << endl;
									cout << "\nMessage Is Too Long.Please Try Again." << endl;
									cout << "\n\nPress 2 to go to Message Option." << endl;
									cout << "Press 0 to go to Phone Menu." << endl;
								}
								else
								{
									int option;
									int chooser;

									cout << "\n\nOption:" << "\n1.By Number" << "\n2.From Contacts List" <<endl;

									cout << "\nSelect : ";
									cin >> option;

									if(option==1)
									{
										cout << "\nEnter Phone Number: ";
										cin >> PhnNum;

										if(PhnNum.compare(p.registerPhone[num-1].getPhnNumber())!=0) //check registered phone number
										{
											if(PhnNum.length()>=8 && PhnNum.length()<=16) //check number length
											{
												if(isNumber(PhnNum)) //check string
												{
													int loop;
													checker = 0;

													Message tempMsg;

													for(loop=0;loop<p.registerPhone[num-1].Contact.size();loop++) //for all contact from list
													{
														if(PhnNum.compare(p.registerPhone[num-1].Contact[loop].getPersonNumber())==0) //check registered phone number
														{
															checker = 1;
															break;
														}
													}

													if(checker==1)
													{
														tempMsg.setPersonName(p.registerPhone[num-1].Contact[loop].getPersonName()); //set contact name
													}
													else
													{
														tempMsg.setPersonName("Unknown");
													}

													tempMsg.setPhoneNumber(PhnNum); //send phone number
													tempMsg.setMessage(msg); //set message
													tempMsg.setStartDateTime(Time()); //send present time& date

													p.registerPhone[num-1].AddMessage(tempMsg); //send an object

													cout << "\nsending..." << endl;
													Sleep(1000); //hold 1 second
													cout << "\nMessage Successfully Sent." << endl;
													Sleep(1000); //hold 1 second

													//for save message history a text file
													ofstream outfile;
													outfile.open("messagehistory.txt",ios_base::app);

													outfile << "Message: " << tempMsg.getMessage() << endl;
													outfile << "Name: " << tempMsg.getPersonName() << endl;
													outfile << "Phone Number: " << tempMsg.getPhoneNumber() << endl;
													outfile << "Time & Date: " << tempMsg.getStartDateTime();
													outfile << "Message Cost: " << tempMsg.getCost() << "\n\n" << endl;

													outfile.close();

													clrscr(); //clear screen

													cout << "\tMESSAGE" << endl;
													cout << "\n21.Send Message" << "\n22.Message History" << "\n23.Delete All History" << endl;
													cout << "\nPress 0 to go to Phone Menu." << endl;
												}
												else
												{
													clrscr(); //clear screen

													cout << "\tMESSAGE" << endl;
													cout << "\nInvalid Number." << endl;
													cout << "\n\nPress 2 to go to Message Option." << endl;
													cout << "Press 0 to go to Phone Menu." << endl;
												}
											}
											else
											{
												clrscr(); //clear screen

												cout << "\tMESSAGE" << endl;
												cout << "\nInvalid Number." << endl;
												cout << "\n\nPress 2 to go to Message Option." << endl;
												cout << "Press 0 to go to Phone Menu." << endl;
											}
										}
										else
										{
											clrscr(); //clear screen

											cout << "\tMESSAGE" << endl;
											cout << "\nThis Is Your Registration Number.Choose Another Number To Message." << endl;
											cout << "\n\nPress 2 to go to Message Option." << endl;
											cout << "Press 0 to go to Phone Menu." << endl;
										}
									}
									else if(option==2)
									{
										clrscr(); //clear screen

										cout << "\tCONTACTS LIST" << endl;

										vector<PhoneBook> contacts = p.registerPhone[num-1].getContactsList(); //all contact list

										for(int j=0 ; j<contacts.size() ; j++)
										{
											cout << "\n" << j+1 << "." << endl; //show number
											cout << "Name : " << contacts[j].getPersonName() << endl; //show contact name
										    cout << "Phone Number : " << contacts[j].getPersonNumber() << endl; //show contact number
										}

										if(contacts.size()>0)
										{
											cout << "\n\nSelect A contact by Serial Number To Send Message.";
											cout << "Select : ";
											cin >> chooser;


											if(chooser>0 && chooser<p.registerPhone[num-1].Contact.size()+1) //choose one contact
											{
												PhnNum = p.registerPhone[num-1].Contact[chooser-1].getPersonNumber(); //take phone number

												if(PhnNum.compare(p.registerPhone[num-1].getPhnNumber())!=0) //check registered phone number
												{
													if(PhnNum.length()>=8 && PhnNum.length()<=16) //check phone number length
													{
														if(isNumber(PhnNum)) //check string
														{
															Message tempMsg; //Message class object declare

															tempMsg.setPersonName(p.registerPhone[num-1].Contact[chooser-1].getPersonName()); //send contact name
															tempMsg.setPhoneNumber(PhnNum); //send phone number
															tempMsg.setMessage(msg); //send message
															tempMsg.setStartDateTime(Time()); //send present time& date

															p.registerPhone[num-1].AddMessage(tempMsg); //send an object

															cout << "\nsending..." << endl;
															Sleep(1000); //hold 1 second
															cout << "\nMessage Successfully Sent." << endl;
															Sleep(1000); //hold 1 second

															//for save message history a text file
															ofstream outfile;
															outfile.open("messagehistory.txt",ios_base::app);

															outfile << "Message: " << tempMsg.getMessage() << endl;
															outfile << "Name: " << tempMsg.getPersonName() << endl;
															outfile << "Phone Number: " << tempMsg.getPhoneNumber() << endl;
															outfile << "Time & Date: " << tempMsg.getStartDateTime();
															outfile << "Message Cost: " << tempMsg.getCost() << "\n\n" << endl;

															outfile.close();

															clrscr(); //clear screen

															cout << "\tMESSAGE" << endl;
															cout << "\n21.Send Message" << "\n22.Message History" << "\n23.Delete All History" << endl;
															cout << "\nPress 0 to go to Phone Menu." << endl;
														}
														else
														{
															clrscr(); //clear screen

															cout << "\tMESSAGE" << endl;
															cout << "\nInvalid Number." << endl;
															cout << "\n\nPress 2 to go to Message Option." << endl;
															cout << "Press 0 to go to Phone Menu." << endl;
														}
													}
													else
													{
														clrscr(); //clear screen

														cout << "\tMESSAGE" << endl;
														cout << "\nInvalid Number." << endl;
														cout << "\n\nPress 2 to go to Message Option." << endl;
														cout << "Press 0 to go to Phone Menu." << endl;
													}
												}
												else
												{
													clrscr(); //clear screen

													cout << "\tMESSAGE" << endl;
													cout << "\nThis Is Your Registration Number.Choose Another Number To Message." << endl;
													cout << "\n\nPress 2 to go to Message Option." << endl;
													cout << "Press 0 to go to Phone Menu." << endl;
												}
											}
											else
											{
												clrscr(); //clear screen

												cout << "\tMESSAGE" << endl;
												cout << "\nSerial Number Did Not Match." << endl;
												cout << "\n\nPress 2 to go to Message Option." << endl;
												cout << "Press 0 to go to Phone Menu." << endl;
											}
										}
										else
										{
											clrscr(); //clear screen

											cout << "\tMESSAGE" << endl;
											cout << "\nNo Contact Number." << endl;
											cout << "\n\nPress 3 to go to PhoneBook Option." << endl;
											cout << "Press 0 to go to Phone Menu." << endl;
										}

									}
									else
									{
										clrscr(); //clear screen

										cout << "\tMESSAGE" << endl;
										cout << "\nPlease Follow The Instruction." << endl;
										cout << "\n\nPress 2 to go to Message Option." << endl;
										cout << "Press 0 to go to Phone Menu." << endl;
									}
								}
				            }
				        }
						else if(select==22) //message history option
				        {
				            clrscr(); //clear screen

				            cout << "\tMESSAGE HISTORY" << endl;

							vector<Message> mssgs = p.registerPhone[num-1].getMessageHistory(); //all message history
				            for(int j=0 ; j<mssgs.size() ; j++)
				            {
								cout << "\n" << j+1 << "." << endl; //show serial number
								cout << "Message :\n" << mssgs[j].getMessage() << "\n" << endl; //show message
								cout << "Name : " << mssgs[j].getPersonName() << endl; //show receiver name
				                cout << "Phone Number : " << mssgs[j].getPhoneNumber() << endl; //print phone number
				                cout << "Time & Date : " << mssgs[j].getStartDateTime() ; //print time & date
								cout << "Message Cost : " << mssgs[j].getCost() << " tk.\n" << endl; //show message cost
				            }

							if(p.registerPhone[num-1].Mssg.size()>0)
							{
								int chooseH;

								cout << "\n\nSelect A History by Serial Number To Delete,Otherwise Press 0.";

								cout << "\nSelect : ";
								cin >> chooseH;

								if(chooseH>0 && chooseH<p.registerPhone[num-1].Mssg.size()+1) //choose a message
								{
									p.registerPhone[num-1].Mssg.erase(p.registerPhone[num-1].Mssg.begin()+chooseH-1); //delete message history

									clrscr(); //clear screen

									cout << "\tERASE MESSAGE HISTORY" << endl;

									cout << "\ndeleting..." << endl;
									Sleep(1000); //hold 1 second
									cout << "\nMESSAGE Successfully Deleted." << endl;
									Sleep(1000); //hold 1 second

									clrscr(); //clear screen

									cout << "\tMESSAGE" << endl;
									cout << "\n21.Send Message" << "\n22.Message History" << "\n23.Delete All History" << endl;
									cout << "\nPress 0 to go to Phone Menu." << endl;
								}
								else if(chooseH==0)
								{
									clrscr(); //clear screen

									cout << "\tMESSAGE" << endl;
									cout << "\n21.Send Message" << "\n22.Message History" << "\n23.Delete All History" << endl;
									cout << "\nPress 0 to go to Phone Menu." << endl;
								}
								else
								{
									clrscr(); //clear screen

									cout << "\tMESSAGE HISTORY" << endl;
									cout << "\nSerial Number Did Not Match." << endl;
									cout << "\n\nPress 5 to go to Call History Option." << endl;
									cout << "Press 0 to go to Phone Menu." << endl;
								}
							}
							else
							{
								clrscr(); //clear screen

								cout << "\tMESSAGE HISTORY" << endl;
								cout << "\nNo Messages." << endl;
								cout << "\n\nPress 2 to go to Message option." << endl;
								cout << "Press 0 to go to Phone Menu." << endl;
							}
				        }
						else if(select==23)
						{
							p.registerPhone[num-1].Mssg.clear();

							clrscr(); //clear screen

							cout << "\tMESSAGE HISTORY" << endl;

							cout << "\ndeleting..." << endl;
							Sleep(1000); //hold 1 second
							cout << "\nMessage History Empty." << endl;
							Sleep(1000); //hold 1 second

							clrscr(); //clear screen

							cout << "\tMESSAGE" << endl;
							cout << "\n21.Send Message" << "\n22.Message History" << "\n23.Delete All History" << endl;
							cout << "\nPress 0 to go to Phone Menu." << endl;
						}
						else if(select==3)
				        {
				            clrscr(); //clear screen

							cout << "\tPHONEBOOK" << endl;
				            cout << "\n31.Add Contact" << "\n32.Contacts List" << "\n33.Delete All"  << endl;
				            cout << "\nPress 0 to go to Phone Menu." << endl;
				        }
						else if(select==31)
						{
							clrscr(); //clear screen

				            cout << "\tADD CONTACT" << endl;
							cout << "\nEnter Number : ";
							cin >> PhnNum;

							if(isNumber(PhnNum)) //check string
							{
								cout << "\nEnter Name : ";

								cin.ignore();
								getline(cin,name); //write contact person name
								cin.clear();

								PhoneBook tempPhnBook; //PhoneBook class object declare
								tempPhnBook.setPersonNumber(PhnNum); //send phone number
								tempPhnBook.setPersonName(name); //send phone name

								p.registerPhone[num-1].AddContact(tempPhnBook); //send an object

								cout << "\nadding..." << endl;
								Sleep(1000); //hold 1 second
								cout << "\nSuccessfully Added." << endl;
								Sleep(1000); //hold 1 second

								//for save contact list in a text file
								ofstream outfile;
								outfile.open("contactlist.txt",ios_base::app);

								outfile << "Name: " << tempPhnBook.getPersonName() << endl;
								outfile << "Phone Number: " <<tempPhnBook.getPersonNumber() << "\n\n" << endl;

								outfile.close();

								clrscr(); //clear screen

								cout << "\tPHONEBOOK" << endl;
								cout << "\n31.Add Contact" << "\n32.Contacts List" << "\n33.Delete All"  << endl;
								cout << "\nPress 0 to go to Phone Menu." << endl;
							}
							else
							{
								clrscr(); //clear screen

								cout << "\tPHONEBOOK" << endl;
								cout << "\nInvalid Number." << endl;
								cout << "\n\nPress 3 to go to PhoneBook Option." << endl;
								cout << "Press 0 to go to Phone Menu." << endl;
							}

						}
						else if(select==32)
						{
							clrscr(); //clear screen

				            cout << "\tCONTACTS LIST" << endl;

							vector<PhoneBook> contacts = p.registerPhone[num-1].getContactsList();

				            for(int j=0 ; j<contacts.size() ; j++)
				            {
								cout << "\n" << j+1 << "." << endl; //show serial number
								cout << "Name : " << contacts[j].getPersonName() << endl; //show contact person name
				                cout << "Phone Number : " << contacts[j].getPersonNumber() << endl; //show contact person number
				            }

							if(p.registerPhone[num-1].Contact.size()>0)
							{
								int chooser;

								cout << "\n\nSelect A Contact by Serial Number To Get Some Options,Otherwise Press 0.";

								cout << "\nSelect : ";
								cin >> chooser;

								if(chooser>0 && chooser<p.registerPhone[num-1].Contact.size()+1) //choose a contact
								{
									clrscr(); //clear screen

									cout << "\tOPTIONS" << "\n\n1.Call" << "\n2.Message" << "\n3.Edit" << "\n4.Delete" <<endl;
                                    cout << "\nPress 100 to go to PhoneBook Option." << endl;

									while(1)
                                    {
                                        int option;
                                        cout << "\nSelect : ";
                                        cin >> option;

                                        if(option==0) //contact option
                                        {
                                            clrscr(); //clear screen

                                            cout << "\tOPTIONS" << "\n\n1.Call" << "\n2.Message" << "\n3.Edit" << "\n4.Delete" << endl;
                                            cout << "\nPress 100 to go to PhoneBook Option." << endl;
                                        }
                                        else if(option==1) //call option
                                        {
                                            clrscr(); //clear screen

                                            if( p.registerPhone[num-1].getCredit() < 1) //check credit to make call
                                            {
                                                clrscr(); //clear screen

                                                cout << "\tCALL" << endl;
                                                cout << "\nPlease Recharge First." << endl;
                                                cout << "\n\nPress 0 to go to Options." << endl;
                                            }
                                            else
                                            {
                                                cout << "\tCALL" << endl;

                                                PhnNum = p.registerPhone[num-1].Contact[chooser-1].getPersonNumber(); //take phone number from contact

                                                cout<<"\nconnecting...\n";
                                                Sleep(1000); //hold 1 second

                                                if(PhnNum.compare(p.registerPhone[num-1].getPhnNumber())!=0) //check registered number
                                                {
                                                    if(PhnNum.length()>=8 && PhnNum.length()<=16) //check phone number length
                                                    {
                                                        if(isNumber(PhnNum)) //check string
                                                        {
                                                            double creditCheck = p.registerPhone[num-1].getCredit(); //check credit

															int durationMax = creditCheck/0.02 - 2; //check max duration

															int duration = CallClock(durationMax); //show CallClock

                                                            cout<<"\ncall end...\n";
                                                            Sleep(1000); //hold 1 second

                                                            PhoneCall tempCall; //PhoneCall class object declare

                                                            tempCall.setPersonName(p.registerPhone[num-1].Contact[chooser-1].getPersonName()); //send contact name
                                                            tempCall.setPhoneNumber(PhnNum); //send phone number
                                                            tempCall.setStartDateTime(Time()); //send present time& date

															if(duration<2) //for miss call option
															{
																tempCall.setCallDuration(0); //send call duration
																tempCall.setPerSecondCallCost(0); //send per second call cost
															}
															else
															{
																tempCall.setCallDuration(duration); //send call duration
																tempCall.setPerSecondCallCost(0.02); //fix per second call cost
															}

                                                            p.registerPhone[num-1].AddCall(tempCall); //send an object

															//for save call history a text file
															ofstream outfile;
															outfile.open("callhistory.txt",ios_base::app);

															outfile << "Name: " << tempCall.getPersonName() << endl;
															outfile << "PhoneNumber: " << tempCall.getPhoneNumber() << endl;
															outfile << "Time & Date: " << tempCall.getStartDateTime();
															outfile << "Call Duration: " << tempCall.getCallDuration() <<endl;
															outfile << "Call Cost: " << tempCall.getCost() << "\n\n" << endl;

															outfile.close();

                                                            clrscr(); //clear screen

                                                            cout << "\tOPTIONS" << "\n\n1.Call" << "\n2.Message" << "\n3.Edit" << "\n4.Delete" <<endl;
                                                            cout << "\nPress 100 to go to PhoneBook Option." << endl;
                                                        }
                                                        else
                                                        {
                                                            clrscr(); //clear screen

                                                            cout << "\tCALL" << endl;
                                                            cout << "\nInvalid Number." << endl;
                                                            cout << "\n\nPress 0 to go to Options." << endl;
                                                        }
                                                    }
                                                    else
                                                    {
                                                        clrscr(); //clear screen

                                                        cout << "\tCALL" << endl;
                                                        cout << "\nInvalid Number." << endl;
                                                        cout << "\n\nPress 0 to go to Options." << endl;
                                                    }
                                                }
                                                else
                                                {
                                                    clrscr(); //clear screen

                                                    cout << "\tCALL" << endl;
                                                    cout << "\nThis Is Your Registration Number.Choose Another Number To Call." << endl;
                                                    cout << "\n\nPress 0 to go to Options." << endl;
                                                }
                                            }
                                        }
                                        else if(option==2) //message option
                                        {
                                            clrscr(); //clear screen

                                            if( p.registerPhone[num-1].getCredit() < 5) //check credit to make call
                                            {
                                                clrscr(); //clear screen

                                                cout << "\tMESSAGE" << endl;
                                                cout << "\nPlease Recharge First." << endl;
                                                cout << "\n\nPress 0 to go to Options." << endl;
                                            }
                                            else
                                            {
                                                cout << "\tSEND MESSAGE" << endl;

                                                cout << "\nEnter Your Message : " <<endl;

                                                cin.ignore();
                                                getline(cin,msg); //write message
                                                cin.clear();

                                                if(msg.size()>600) //check message length
                                                {
                                                    clrscr(); //clear screen

                                                    cout << "\tMESSAGE" << endl;
                                                    cout << "\nMessage Is Too Long.Please Try Again." << endl;
                                                    cout << "Press 0 to go to Options." << endl;
                                                }
                                                else
                                                {
                                                    PhnNum = p.registerPhone[num-1].Contact[chooser-1].getPersonNumber(); //take contact phone number

                                                    if(PhnNum.compare(p.registerPhone[num-1].getPhnNumber())!=0) //check registered phone number
                                                    {
                                                        if(PhnNum.length()>=8 && PhnNum.length()<=16) //check contact number length
                                                        {
                                                            if(isNumber(PhnNum)) //check string
                                                            {
                                                                Message tempMsg; //Message class object declare

                                                                tempMsg.setPersonName(p.registerPhone[num-1].Contact[chooser-1].getPersonName()); //send contact name
                                                                tempMsg.setPhoneNumber(PhnNum); //send phone number
                                                                tempMsg.setMessage(msg); //send message
                                                                tempMsg.setStartDateTime(Time()); //send present time& date

                                                                p.registerPhone[num-1].AddMessage(tempMsg); //send an object

                                                                cout << "\nsending..." << endl;
                                                                Sleep(1000); //hold 1 second
                                                                cout << "\nMessage Successfully Sent." << endl;
                                                                Sleep(1000); //hold 1 second

																//for save message history a text file
																ofstream outfile;
																outfile.open("messagehistory.txt",ios_base::app);

																outfile << "Message: " << tempMsg.getMessage() << endl;
																outfile << "Name: " << tempMsg.getPersonName() << endl;
																outfile << "Phone Number: " << tempMsg.getPhoneNumber() << endl;
																outfile << "Time & Date: " << tempMsg.getStartDateTime();
																outfile << "Message Cost: " << tempMsg.getCost() << "\n\n" << endl;

																outfile.close();

                                                                clrscr(); //clear screen

                                                                cout << "\tOPTIONS" << "\n\n1.Call" << "\n2.Message" << "\n3.Edit" << "\n4.Delete" <<endl;
                                                                cout << "\nPress 100 to go to PhoneBook Option." << endl;
                                                            }
                                                            else
                                                            {
                                                                clrscr(); //clear screen

                                                                cout << "\tMESSAGE" << endl;
                                                                cout << "\nInvalid Number." << endl;
                                                                cout << "\n\nPress 0 to go to Options." << endl;
                                                            }
                                                        }
                                                        else
                                                        {
                                                            clrscr(); //clear screen

                                                            cout << "\tMESSAGE" << endl;
                                                            cout << "\nInvalid Number." << endl;
                                                            cout << "\n\nPress 0 to go to Options." << endl;
                                                        }
                                                    }
                                                    else
                                                    {
                                                        clrscr(); //clear screen

                                                        cout << "\tMESSAGE" << endl;
                                                        cout << "\nThis Is Your Registration Number.Choose Another Number To Message." << endl;
                                                        cout << "\n\nPress 0 to go to Options." << endl;
                                                    }
                                                }
                                            }
                                        }
                                        else if(option==3) //edit contact option
                                        {
                                            name = p.registerPhone[num-1].Contact[chooser-1].getPersonName(); //take contact name
                                            PhnNum = p.registerPhone[num-1].Contact[chooser-1].getPersonNumber(); //take contact number

                                            clrscr(); //clear screen

                                            cout << "\tEDIT CONTACT" << endl;
                                            cout << "\n1.Edit Name" << "\n2.Edit Phone Number" << endl;
                                            cout << "\nPress 0 to go to Options.";

                                            int choose=0;

                                            cout << "\n\nSelect : ";
                                            cin >> choose;

                                            if(choose==1) // edit name option
                                            {
                                                clrscr(); //clear screen

                                                cout << "\tNAME EDITING" << endl;

                                                cout << "\nEnter Name : ";

                                                cin.ignore();
                                                getline(cin,name); //write name
                                                cin.clear();

                                                p.registerPhone[num-1].Contact[chooser-1].setPersonName(name); //send contact's edited name

                                                cout << "\nediting..." << endl;
                                                Sleep(1000); //hold 1 second
                                                cout << "\nSuccessfully Edited." << endl;
                                                Sleep(1000); //hold 1 second

                                                clrscr(); //clear screen

                                                cout << "\tOPTIONS" << "\n\n1.Call" << "\n2.Message" << "\n3.Edit" << "\n4.Delete" <<endl;
                                                cout << "\nPress 100 to go to PhoneBook Option." << endl;
                                            }
                                            else if(choose==2) //edit number option
                                            {
                                                clrscr(); //clear screen

                                                cout << "\tNUMBER EDITING" << endl;

                                                cout << "\nEnter Number : ";
                                                cin >> PhnNum; //write number

                                                if(isNumber(PhnNum)) //check string
                                                {
                                                    p.registerPhone[num-1].Contact[chooser-1].setPersonNumber(PhnNum); //send number

                                                    cout << "\nediting..." << endl;
                                                    Sleep(1000); //hold 1 second
                                                    cout << "\nSuccessfully Edited." << endl;
                                                    Sleep(1000); //hold 1 second

                                                    clrscr(); //clear screen

                                                    cout << "\tOPTIONS" << "\n\n1.Call" << "\n2.Message" << "\n3.Edit" << "\n4.Delete" <<endl;
                                                    cout << "\nPress 100 to go to PhoneBook Option." << endl;
                                                }
                                                else
                                                {
                                                    clrscr(); //clear screen

                                                    cout << "\tOPTIONS" << endl;
                                                    cout << "\nInvalid Number." << endl;
                                                    cout << "\n\nPress 0 to go to Options." << endl;
                                                }
                                            }
                                            else if(choose==0) //back to option
                                            {
                                                clrscr(); //clear screen

                                                cout << "\tOPTIONS" << "\n\n1.Call" << "\n2.Message" << "\n3.Edit" << "\n4.Delete" <<endl;
                                                cout << "\nPress 100 to go to PhoneBook Option." << endl;
                                            }
                                            else
                                            {
                                                clrscr(); //clear screen

                                                cout << "\tOPTIONS" << endl;
                                                cout << "\nPlease Follow The Instruction." << endl;
                                                cout << "\n\nPress 0 to go to OptionS." << endl;
                                            }
                                        }
                                        else if(option==4) //delete contact
                                        {
                                            p.registerPhone[num-1].Contact.erase(p.registerPhone[num-1].Contact.begin()+chooser-1); //delete contact from list

                                            clrscr(); //clear screen

                                            cout << "\tERASE CONTACT" << endl;

                                            cout << "\ndeleting..." << endl;
                                            Sleep(1000); //hold 1 second
                                            cout << "\nContact Successfully Deleted." << endl;
                                            Sleep(1000); //hold 1 second

                                            clrscr(); //clear screen

                                            cout << "\tOPTIONS" << "\n\n1.Call" << "\n2.Message" << "\n3.Edit" << "\n4.Delete" <<endl;
                                            cout << "\nPress 100 to go to PhoneBook Option." << endl;
                                        }
                                        else if(option==100) //back to contact option
                                        {
                                            clrscr(); //clear screen

                                            cout << "\tPHONEBOOK" << endl;
                                            cout << "\n31.Add Contact" << "\n32.Contacts List" << "\n33.Delete All"  << endl;
                                            cout << "\nPress 0 to go to Phone Menu." << endl;

											break;
                                        }
                                        else
                                        {
                                            clrscr(); //clear screen

                                            cout << "\tOPTIONS" << endl;
                                            cout << "\nPlease Follow The Instruction." << endl;
                                            cout << "\n\nPress 0 to go to Options." << endl;

                                        }
                                    }
								}
								else if(chooser==0)
								{
									clrscr(); //clear screen

									cout << "\tPHONEBOOK" << endl;
									cout << "\n31.Add Contact" << "\n32.Contacts List" << "\n33.Delete All"  << endl;
									cout << "\nPress 0 to go to Phone Menu." << endl;
								}
								else
								{
									clrscr(); //clear screen

									cout << "\tCONTACTS LIST" << endl;
									cout << "\nSerial Number Did Not Match." << endl;
									cout << "\n\nPress 3 to go to PhoneBook Option." << endl;
									cout << "Press 0 to go to Phone Menu." << endl;
								}
							}
							else
							{
								clrscr(); //clear screen

								cout << "\tCONTACTS LIST" << endl;
								cout << "\nNo Contact Number." << endl;
								cout << "\n\nPress 3 to go to PhoneBook Option." << endl;
								cout << "Press 0 to go to Phone Menu." << endl;
							}
						}
						else if(select==33) //delete all contacts from list
						{
							p.registerPhone[num-1].Contact.clear(); //delete

							clrscr(); //clear screen

							cout << "\tCONTACTS LIST" << endl;

							cout << "\ndeleting..." << endl;
							Sleep(1000); //hold 1 second
							cout << "\nContact List Empty." << endl;
							Sleep(1000); //hold 1 second

							clrscr(); //clear screen

							cout << "\tPHONEBOOK" << endl;
							cout << "\n31.Add Contact" << "\n32.Contacts List" << "\n33.Delete All"  << endl;
							cout << "\nPress 0 to go to Phone Menu." << endl;
						}
				        else if(select==4) //credit option
				        {
				            clrscr(); //clear screen

							cout << "\tCREDIT" << endl;
				            cout << "\n41.Add Credit" << "\n42.See Credit" << "\n43.Per Second Call Cost" << "\n44.Per Message Cost" << endl;
				            cout << "\nPress 0 to go to Phone Menu." << endl;
				        }
				        else if(select==41) //add credit option
				        {
				            float credit;

				            clrscr(); //clear screen

				            cout << "\tADD CREDIT" << endl;
				            cout << "\nEnter Credit: ";
				            cin >> credit;

				            if(credit>500 || credit<10) //check credit
							{
								clrscr(); //clear screen

								cout << "\tADD CREDIT" << endl;
								cout << "\nYou Can't Add This Amount.You Can Add 10-500 tk." << endl;
								cout << "\nPress 4 to go to Credit Option." << endl;
								cout << "Press 0 to go to Phone Menu." << endl;
							}
							else
							{
								cout << "\nRecharged Successful." << endl;
								Sleep(1000); //hold 1 second

								p.registerPhone[num-1].setCredit(credit); //send balance

								clrscr(); //clear screen

								cout << "\tCREDIT" << endl;
								cout << "\n41.Add Credit" << "\n42.See Credit" << "\n43.Per Second Call Cost" << "\n44.Per Message Cost" << endl;
								cout << "\nPress 0 to go to Phone Menu." << endl;
							}
				        }
				        else if(select==42) //see credit
				        {
				            clrscr(); //clear screen

				            cout << "\tSEE CREDIT" << endl;
							cout << "\nYour current balance is : " << p.registerPhone[num-1].getCredit() << " tk." << endl;

							cout << "\n\nPress 4 to go to Credit Option." << endl;
				            cout << "Press 0 to go to Phone Menu." << endl;
				        }
				        else if(select==43) //per second call cost
				        {
				            clrscr(); //clear screen

				            cout << "\tPER SECOND CALL COST" << endl;
				            cout << "\nPer second call cost is : 0.02 tk." << endl;

				            cout << "\n\nPress 4 to go to Credit Option." << endl;
				            cout << "Press 0 to go to Phone Menu." << endl;
				        }
						else if(select==44) //per message cost
				        {
				            clrscr(); //clear screen

				            cout << "\tPER MESSAGE COST" << endl;
				            cout << "\nPer message cost is : 1.15 tk." << endl;

				            cout << "\n\nPress 4 to go to Credit Option." << endl;
				            cout << "Press 0 to go to Phone Menu." << endl;
				        }
						else if(select==5) //call history option
						{
							clrscr(); //clear screen

							cout << "\tCALL HISTORY" << endl;
							cout << "\n51.See History" << "\n52.Delete All"  << endl;
							cout << "\nPress 0 to go to Phone Menu." << endl;

						}
				        else if(select==51) //see history
				        {
				            clrscr(); //clear screen

				            cout << "\tCALL HISTORY" << endl;

							vector<PhoneCall> calls = p.registerPhone[num-1].getCallHistory(); //all call history

				            for(int j=0 ; j<calls.size() ; j++)
				            {
								cout << "\n"  << j+1 << "." << endl;
								cout << "Name : " << calls[j].getPersonName() << endl; //show name

								second = calls[j].getCallDuration();

				                if(second!=0)
								{
									cout << "Phone Number : " << calls[j].getPhoneNumber() << endl; //print phone number
									cout << "Time & Date : " << calls[j].getStartDateTime() ; //print time & date

									cout << "Call Duration : ";
									TimeConvert(second);

									cout << "Call Cost : " << calls[j].getCost() << " tk.\n" << endl;
								}
								else
								{
									cout << "Phone Number : " << calls[j].getPhoneNumber() << "  (missed call)" << endl; //print phone number
									cout << "Time & Date : " << calls[j].getStartDateTime() ; //print time & date

									cout << "Call Duration : ";
									TimeConvert(second); //time convert(second to minute)

									cout << "Call Cost : " << calls[j].getCost() << " tk.\n" << endl; //show call cost
								}
				            }

							if(p.registerPhone[num-1].CallLog.size()>0)
							{
								int chooseH;

								cout << "\n\nSelect A History by Serial Number To Delete,Otherwise Press 0.";

								cout << "\nSelect : ";
								cin >> chooseH;

								if(chooseH>0 && chooseH<p.registerPhone[num-1].CallLog.size()+1) //choose call history
								{
									p.registerPhone[num-1].CallLog.erase(p.registerPhone[num-1].CallLog.begin()+chooseH-1);

									clrscr(); //clear screen

									cout << "\tERASE CALL LOG" << endl;

									cout << "\ndeleting..." << endl;
									Sleep(1000); //hold 1 second
									cout << "\nCall Log Successfully Deleted." << endl;
									Sleep(1000); //hold 1 second

									clrscr(); //clear screen

									cout << "\tCALL HISTORY" << endl;
									cout << "\n51.See History" << "\n52.Delete All"  << endl;
									cout << "\nPress 0 to go to Phone Menu." << endl;
								}
								else if(chooseH==0)
								{
									clrscr(); //clear screen

									cout << "\tCALL HISTORY" << endl;
									cout << "\n51.See History" << "\n52.Delete All"  << endl;
									cout << "\nPress 0 to go to Phone Menu." << endl;
								}
								else
								{
									clrscr(); //clear screen

									cout << "\tCALL HISTORY" << endl;
									cout << "\nSerial Number Did Not Match." << endl;
									cout << "\n\nPress 5 to go to Call History Option." << endl;
									cout << "Press 0 to go to Phone Menu." << endl;
								}
							}
							else
							{
								clrscr(); //clear screen

								cout << "\tCALL HISTORY" << endl;
								cout << "\nNo Call Log." << endl;
								cout << "\n\nPress 5 to go to Call History option." << endl;
								cout << "Press 0 to go to Phone Menu." << endl;
							}
				        }
						else if(select == 52)
						{
							p.registerPhone[num-1].CallLog.clear();

							clrscr(); //clear screen

							cout << "\tCALL LOGS" << endl;

							cout << "\ndeleting..." << endl;
							Sleep(1000);
							cout << "\nCall History Empty." << endl;
							Sleep(1000);

							clrscr(); //clear screen

							cout << "\tCALL HISTORY" << endl;
							cout << "\n51.See History" << "\n52.Delete All"  << endl;
							cout << "\nPress 0 to go to Phone Menu." << endl;
						}
				        else if(select==100) //quit option
				        {
				            clrscr(); //clear screen

				            cout << "\tREGISTER MENU\n" << "\n1.Register\n" << "2.Registered Phone\n" << "3.All Phones Options" << endl;
							cout << "\nPress 100 to Quit" << endl;

							break;
				        }
				        else
				        {
				            clrscr(); //clear screen

							cout << "\tPHONE MENU" << endl;
				            cout << "\nPlease Follow The Instruction." << endl;
				            cout << "\n\nPress 0 to go to Phone Menu." << endl;
				        }
					}
				}
				else if(num==0) //back to register phone menu
				{
					clrscr(); //clear screen

				    cout << "\tREGISTER MENU\n" << "\n1.Register\n" << "2.Registered Phone List\n" << "3.All Phones Options" << endl;
					cout << "\nPress 100 to Quit" << endl;
				}
				else
				{
					clrscr(); //clear screen

					cout << "\tREGISTERED PHONE LIST" << endl;
					cout << "\nSerial Number Did Not Match." << endl;
					cout << "\n\nPress 0 to go to Register Menu." << endl;
				}
			}
			else
			{
				cout << "Please Register First." << endl;
				cout << "\n\nPress 0 to go to Register Menu." << endl;
			}
        }
		else if(select==3) // all phones options
		{
			clrscr(); //clear screen

			cout << "\tALL PHONES" << endl;
			cout << "\n31.Total Credit" << "\n32.Average Duration" << "\n33.Total Cost"  << endl;
			cout << "\nPress 0 to go to Register Menu." << endl;
		}
		else if(select==31) //total credit
		{
			clrscr(); //clear screen

			cout << "\tTOTAL CREDIT" << endl;

			if(p.registerPhone.size()>0)
			{
				float Tcredit = 0;

				for(int i=0; i<p.registerPhone.size() ; i++)
				{
					Tcredit += p.registerPhone[i].getCredit(); //add credit
					cout << "\nCredit of " << i+1 << "th Phone : " << p.registerPhone[i].getCredit() << " tk." << endl;
				}

				cout << "\n\nTotal Credit is : " << Tcredit << " tk." << endl;
			}
			else
			{
				cout << "\nPlease Register First." << endl;
			}
			cout << "\n\nPress 3 to go to All Phones Options." << endl;
			cout << "Press 0 to go to Register Menu." << endl;
		}
		else if(select==32) //average length
		{
			clrscr(); //clear screen

			cout << "\tAVERAGE DUARTION" << endl;

			int i;
			int check=0;
			int count= 0;
			int callCounterEachPhone=0;
			double duration = 0;
			double durationEachPhone = 0;

			if(p.registerPhone.size()>0)
			{
				for(i=0;i<p.registerPhone.size();i++)
				{
					callCounterEachPhone=0;
					durationEachPhone = 0;
					vector<PhoneCall> calls = p.registerPhone[i].getCallHistory();
					for(int j=0;j<calls.size();j++)
					{
						callCounterEachPhone++;
						count++;
						duration += calls[j].getCallDuration(); //add total duration for all phone
						durationEachPhone += calls[j].getCallDuration(); //add total duration for each phone
					}

					if(callCounterEachPhone==0)
					{
						cout << "\nAverage Call Duration Of " << i+1 << "th Phone is : ";
						TimeConvert(0);
					}
					else
					{
						second = durationEachPhone/callCounterEachPhone;
						cout << "\nAverage Call Duration Of " << i+1 << "th Phone is : ";
						TimeConvert(second); //time convert(second to minute)
					}
				}

				cout << "\n\nAverage Call Duration of " << count;

				if(count==1)
                {
                    cout << " Call From ";
                    if(i==1)
                    {
                        cout << i << " Phone is : ";
                        second = duration/count;
                        TimeConvert(second); //time convert(second to minute)
                    }
                    else
                    {
                        cout << i << " Phones is : ";
                        second = duration/count;
                        TimeConvert(second); //time convert(second to minute)
                    }
                }
                else if(count>1)
                {
                    cout << " Calls From ";
                    if(i==1)
                    {
                        cout << i << " Phone is : ";
                        second = duration/count;
                        TimeConvert(second); //time convert(second to minute)
                    }
                    else
                    {
                        cout << i << " Phones is : ";
                        second = duration/count;
                        TimeConvert(second); //time convert(second to minute)
                    }
                }
				else if(count==0)
                {
                    cout << " Call From ";
                    if(i==1)
                    {
                        cout << i << " Phone is : ";
                        second = duration/count;
                        TimeConvert(0);
                    }
                    else
                    {
                        cout << i << " Phones is : ";
                        second = duration/count;
                        TimeConvert(0);
                    }
                }
			}
			else
			{
				cout << "\nPlease Register First." << endl;
			}
			cout << "\n\nPress 3 to go to All Phones Options." << endl;
			cout << "Press 0 to go to Register Menu." << endl;
		}
		else if(select==33) //total cost
		{
			clrscr(); //clear screen

			cout << "\tTOTAL COST" << endl;

			int i;
			double cost = 0;
			double costofEachPhone = 0;

			if(p.registerPhone.size()>0)
			{
				for(i=0;i<p.registerPhone.size();i++)
				{
					costofEachPhone = 0;

					vector<PhoneCall> calls = p.registerPhone[i].getCallHistory();
					for(int j=0;j<calls.size();j++)
					{
						cost += calls[j].getCost();
						costofEachPhone += calls[j].getCost(); //add cost
					}

					vector<Message> mssgs = p.registerPhone[i].getMessageHistory();
					for(int j=0;j<mssgs.size();j++)
					{
						cost += mssgs[j].getCost();
						costofEachPhone += mssgs[j].getCost(); //add cost
					}
					cout << "\nTotal cost of " << i+1 << "th Phone is : " << costofEachPhone << " tk." << endl;
				}
				cout << "\n\nTotal Cost of " << i;
				if(i==1)
                {
                    cout << " Phone is : " << cost << " tk." << endl;
                }
                else
                {
                    cout << " Phones is : " << cost << " tk." << endl;
                }
			}
			else
			{
				cout << "\nPlease Register First." << endl;
			}
			cout << "\n\nPress 3 to go to All Phones Options." << endl;
			cout << "Press 0 to go to Register Menu." << endl;
		}
        else if(select==100) //break the RegisterPhone loop
        {
            break;
        }
        else
        {
            clrscr(); //clear screen

			cout << "\tREGISTER MENU" << endl;
			cout << "\nPlease Follow The Instruction." << endl;
            cout << "\n\nPress 0 to go to Register Menu." << endl;
        }
    }
}



//------------------------------------------------------------------------------------------------
//main function
//------------------------------------------------------------------------------------------------

int main()
{
	allWork();

	cout << "\n\n" << endl;

    return 0;
}

/*

some functions are copied from website & their links given below:



current date&time:
	http://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
clear screen:
	http://stackoverflow.com/questions/17335816/clear-screen-using-c
hold console window:
	http://stackoverflow.com/questions/4184468/sleep-for-milliseconds
press key:
	http://stackoverflow.com/questions/15737495/c-execute-a-while-loop-until-a-key-is-pressed-e-g-esc

*/
