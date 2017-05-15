#include <yarp/os/Network.h>
#include <yarp/os/LogStream.h>
#include <yarp/os/Port.h>
#include <yarp/os/Bottle.h>
#include <yarp/os/Time.h>

//#include <yarp/os/all.h>

using namespace std;
using namespace yarp::os;

int main(int argc, const char **argv) {

    // initialize yarp network
    Network yarp;

    // open the outut port "/relay/out"
    Port outPort;
    if (!outPort.open("/relay/out")) {
        yError() << "cannot open the output port";
        return -1;
    }
	
	 // open the outut port "/relay/in"
    Port inPort;
    if (!inPort.open("/relay/in")) {   //la funzione open restituisce true se e solo se la porta /relay/in è correttamente rilevata
        yError() << "cannot open the input port";
        return -1;
    }

    int counter = 0;
    while (true) {
        counter++;
		
		Bottle input;
        if(!inPort.read(input)) {  //inPort.read() fornisce true se e solo se la lettura va a buon fine
            yError()<<"erro while reading";
            return 0;
        }

        // prepare the output data
        Bottle output;
		output = input;
		output.addString("message sent succesfully");
        output.addInt(counter);
        
        // ...

        // write the output data
        yInfo()<< "writing data ..."; //scrive questo messaggio in tutorial_yarp-port.exe ogniqualvolta si scrive qualcosa nella porta /w
        outPort.write(output);  //scrive i messaggi sulla porta di uscita

        // wait for a second
        Time::delay(1.0);
    }
    return 0;
}
