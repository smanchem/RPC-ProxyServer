// normal_distribution
#include <iostream>
#include <random>

using namespace std;

int main()
{
  const int nrolls=100;  // number of experiments
  const int nstars=100;    // maximum number of stars to distribute

  default_random_engine generator;
  normal_distribution<double> distribution(5.0,2.0);
  
  int p[20]={};
  int s[100]={};
  int j=0;

  for (int i=0; i<nrolls; ++i) {
    double number = distribution(generator);
    if ((number>=0.0)&&(number<20.0)){
	++p[int(number)];
	s[i] = number;
    }
  }

  std::cout << "normal_distribution (5.0,2.0):" << std::endl;

  for (int i=0; i<20; ++i) {
    std::cout << i << "-" << (i+1) << ": ";
    std::cout << std::string(p[i]*nstars/nrolls,'*') << std::endl;
  }
  for(int i=0; i<100;i++){
	if(s[i] == 0) cout<<"\nhttp://www.hindu.com";
	if(s[i] == 1) cout<<"\nhttp://www.bbc.com/news";
	if(s[i] == 2) cout<<"\nhttp://www.theguardian.com/us";
	if(s[i] == 3) cout<<"\nhttp://www.forbes.com";
	if(s[i] == 4) cout<<"\nhttp://www.nytimes.com";
	if(s[i] == 5) cout<<"\nhttp://www.telegraph.co.uk";
	if(s[i] == 6) cout<<"\nhttp://www.google.com";
	if(s[i] == 7) cout<<"\nhttp://www.eenadu.net";
	if(s[i] == 8) cout<<"\nhttp://www.forbes.com";
	if(s[i] == 9) cout<<"\nhttp://www.facebook.com";
	if(s[i] == 10) cout<<"\nhttp://www.time.com";
	if(s[i] == 11) cout<<"\nhttp://www.cnn.com";
	if(s[i] == 12) cout<<"\nhttp://www.nationalgeographic.com";
	if(s[i] == 13) cout<<"\nhttp://www.dailymail.co.uk/ushome/index.html";
	if(s[i] == 14) cout<<"\nhttp://www.washingtonpost.com";
	if(s[i] == 15) cout<<"\nhttp://online.wsj.com";
	if(s[i] == 16) cout<<"\nhttp://america.aljazeera.com";
	if(s[i] == 17) cout<<"\nhttp://www.telegraph.co.uk";
	if(s[i] == 18) cout<<"\nhttp://www.stanford.edu";
	if(s[i] == 19) cout<<"\nhttp://www.cmu.edu";
  } 
  return 0;
}








