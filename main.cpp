#include <iostream>
#include <fstream>
#include "Neuron.h"

using namespace std;

int main()
{
	double current, start, stop;
	cout << "Please specify an external current :" << endl;
	cin >> current;
	cout << "Enter a starting time (in ms) :" << endl;
	cin >> start;
	cout << "Enter an ending time (in ms) :" << endl;
	cin >> stop;
	
	//(double pot [30mV], double res [1 Mohm], double cap, bool ref, double current = 0.0)
	Neuron n (30, 20, 1, false, current);
	n.update(start,stop,current);
	
	//print spike times
	ofstream textfile("spike_times_file");
	vector<double> spikes = n.getSpikeTimes();
	cout << "Spike times: " << endl;
	for (size_t i(0); i<spikes.size(); i++)
	{
		cout << spikes[1] << endl;
		textfile << spikes[1] << endl;
	}
	textfile.close();
	
	return 0;
}
