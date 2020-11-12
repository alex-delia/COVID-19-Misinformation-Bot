# COVID-19 Misinformation Bot

Twitter bot created by students at the University of Western Ontario, aiming to find and correct fake news on the platform related to COVID-19.

## Branches

Please use your own personal branches in the repo for your personal/local work. Once your work is done you can create a PR from that branch to develop.

## Compiling the Code

To run this code locally, you must take the files "libtwitcurl.so" and "libtwitcurl.so.1" and put them in your raspberry pi's /usr/lib directory. We have created a Makefile which runs a g++ command to compile all the files and libraries necessary. Usage is defined below:

```bash
run make in the project directory
```

The command line prompt will either give you an error in the scenario that a tweet has already been posted today, in that scenario, please try and test again the next day before 2pm. Otherwise, the command line prompt will return to you raw json which will indicate that the Tweet has been posted.

You can view all live tweets at @CovidFakeNews on Twitter.

## Raspberry Pi

To work on the live code/folders on the pi the credentials are the following:

```bash
IP ADDRESS: 10.0.0.110
Username: pi
Password: Ask Someone on the team
```

In the documents folder, there are 2 folders which contain code, "3307 Project" and "3307 Project TEST". The first one contains all the live code and will be updated every time a phase is submitted.

**Any Changes for testing on the PI must be made the test folder!!!!**

##

If  you have any questions, feel free to ask any of the team members