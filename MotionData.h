#ifndef _MotionData_h
#define _MotionData_h

#include <vector>
#include <iostream>


class MotionData {

	public:

        int frames;
		double frametime;
		int total_frame_size;

		typedef std::vector<double> fr_data;

		std::vector<fr_data> fr_set;



		MotionData() {
		}

		void loadMotion(std::ifstream& infile);
		void OutputMotion(std::ofstream& Outputfile);

};

#endif
