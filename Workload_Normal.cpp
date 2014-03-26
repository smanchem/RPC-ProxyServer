// normal_distribution
#include <iostream>
#include <random>

using namespace std;

int main()
{
  const int nrolls=50;  // number of experiments
  const int nstars=50;    // maximum number of stars to distribute

  default_random_engine generator;
  normal_distribution<double> distribution(5.0,2.0);
  
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

  std::cout << "normal_distribution (5.0,2.0):" << std::endl;

  for (int i=0; i<10; ++i) {
    std::cout << i << "-" << (i+1) << ": ";
    std::cout << std::string(p[i]*nstars/nrolls,'*') << std::endl;
  }
  for(int i=0; i<50;i++){
	if(s[i] == 0) cout<<"\nwww.hindu.com";
	if(s[i] == 1) cout<<"\nwww.bbc.com/news";
	if(s[i] == 2) cout<<"\nwww.theguardian.com/us";
	if(s[i] == 3) cout<<"\nwww.forbes.com";
	if(s[i] == 4) cout<<"\nwww.nytimes.com";
	if(s[i] == 5) cout<<"\nwww.telegraph.co.uk";
	if(s[i] == 6) cout<<"\nwww.google.com";
	if(s[i] == 7) cout<<"\nwww.eenadu.net";
	if(s[i] == 8) cout<<"\nwww.forbes.com";
	if(s[i] == 9) cout<<"\nwww.facebook.com";
  } 
  return 0;
}
