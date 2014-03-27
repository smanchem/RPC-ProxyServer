// normal_distribution
#include <iostream>
#include <random>

using namespace std;

int main()
{
  const int nrolls=50;  // number of experiments
  const int nstars=50;    // maximum number of stars to distribute

  default_random_engine generator;
  uniform_int_distribution<int> distribution(0,9);
  
  int p[10]={};
  int s[50]={};
  int j=0;

  for (int i=0; i<nrolls; ++i) {
    double number = distribution(generator);
    if ((number>=0.0)&&(number<10.0)){
	++p[int(number)];
	s[i] = number;
    }
  }

  std::cout << "uniform_distribution (0,9):" << std::endl;

  for (int i=0; i<10; ++i) {
    std::cout << i << "-" << (i+1) << ": ";
    std::cout << std::string(p[i]*nstars/nrolls,'*') << std::endl;
  }
  for(int i=0; i<50;i++){
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
  } 
  return 0;
}








