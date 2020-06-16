#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstring>
#include <cmath>

using namespace std;

class closing_prices {
public:
    string _ticker;
    double _d[3];
};

class portfolio {
public:
    string _ticker;
    int _quantity[3];
    double _portfolio_cap[3];
    double _index_weight[3];
    double _delta_weight[3];    
};

class stock_info {
public:
    string _ticker;
    string _name;
    string _industry;
    double _free_float_share;
    double _market_cap[3];
    double _index_weight[3];
};

void calc_portfolio_weight( map<string,portfolio> & m, map<string,closing_prices> & cp, int day ){
    double total_portfolio_cap = 0;
    for( auto & i : m ){
	i.second._portfolio_cap[day] = cp[i.first]._d[day] * i.second._quantity[day];
	total_portfolio_cap += i.second._portfolio_cap[day];
    }
    for( auto & i : m ){
	i.second._index_weight[day] = i.second._portfolio_cap[day] / total_portfolio_cap;
	// cout << "portfolio weight: " << i.second._index_weight[day] << endl;
    }
}

void calc_index_weight( map<string,stock_info> & m, map<string,closing_prices> & cp ){
    double total_market_cap[3] = {0,0,0};
    for( auto & i : m ){
	for( int j = 0; j < 3; ++j ){
	    i.second._market_cap[j] = cp[i.first]._d[j] * i.second._free_float_share;
	    total_market_cap[j] += i.second._market_cap[j];
	}
    }

    double closing_index[3] = {0,0,0};
    for( auto & i : m ){
	// cout << i.second._ticker << ", weight index: ";
	for( int j = 0; j < 3; ++j ){
	    i.second._index_weight[j] = i.second._market_cap[j] / total_market_cap[j];
	    // cout << i.second._index_weight[j] << " ";
	    closing_index[j] += i.second._index_weight[j] * cp[i.first]._d[j];
	    // closing_index[j] += cp[i.first]._d[j];
	}
	// cout << endl;
    }
    for( int j = 0; j < 3; ++j ){
	cout << "closing index: " << closing_index[j] << endl;
    }
}

void calc_delta_weight( map<string,portfolio> & m, map<string,closing_prices> & cp, map<string,stock_info> & si, int day ){
    for( auto & i : m ){
	i.second._delta_weight[day] = si[i.first]._index_weight[day] - i.second._index_weight[day];
	// cout << "day: " << day << ", delta weight: " << i.second._delta_weight[day] << ", index_weight: " << si[i.first]._index_weight[day] << ", portfolio_weight: " << i.second._index_weight[day] << endl;
    }
}


void optimize_portfolio( map<string,portfolio> & m, map<string,closing_prices> & cp, map<string,stock_info> & si, int day, double & cash ){
    for( auto & i : m ){
	i.second._quantity[day] = i.second._quantity[day-1];
    }
    calc_portfolio_weight( m, cp, day );
    calc_delta_weight( m, cp, si, day );
}

int main(){
    double cash = 832704;
    
    fstream f_stock_closing_prices( "index_rebalance_dataset/stocks_closing_prices.csv", fstream::in );
    fstream f_portfolio( "index_rebalance_dataset/portfolio.csv", fstream::in );
    fstream f_stock_info( "index_rebalance_dataset/stocks_info.csv", fstream::in );

    map<string, closing_prices> stock_p;
    {
	string line;
	f_stock_closing_prices >> line;
	while ( f_stock_closing_prices.good() ){
	    closing_prices cp;
	    f_stock_closing_prices >> line;
	    if( !f_stock_closing_prices.good() )
		break;
	    char * split;
	    split = strtok( (char*)line.c_str(), ",");
	    cp._ticker = split;
	    split = strtok( NULL, ",");
	    cp._d[0] = atof(split);
	    split = strtok( NULL, ",");
	    cp._d[1] = atof(split);
	    split = strtok( NULL, ",");
	    cp._d[2] = atof(split);
	    stock_p[cp._ticker] = cp;
	}
    }

    map<string, portfolio> my_portfolio;
    {
	string line;
	f_portfolio >> line;
	while ( f_portfolio.good() ){
	    portfolio p;
	    f_portfolio >> line;
	    if( !f_portfolio.good() )
		break;
	    char * split;
	    split = strtok( (char*)line.c_str(), ",");
	    p._ticker = split;
	    split = strtok( NULL, ",");
	    p._quantity[0] = atoi(split);
	    my_portfolio[p._ticker] = p;
	}
    }

    map<string, stock_info> stock_i;
    {
	char line[256];
	f_stock_info.getline( line, 256,'\n');
	while ( f_stock_info.good() ){
	    stock_info s;
	    f_stock_info.getline( line, 256,'\n');
	    if( !f_stock_info.good() )
		break;
	    char * split;
	    split = strtok( line, ",");
	    s._ticker = split;
	    split = strtok( NULL, ",");
	    s._name = split;
	    split = strtok( NULL, ",");
	    s._industry = split;
	    split = strtok( NULL, ",");
	    s._free_float_share = atof(split);	    
	    stock_i[s._ticker] = s;
	}
    }
    cout << "number of stock prices: " << stock_p.size() << endl;
    cout << "number of portfolio: " << my_portfolio.size() << endl;
    cout << "number of stocks info: " << stock_i.size() << endl;

    calc_index_weight( stock_i, stock_p );

    calc_portfolio_weight( my_portfolio, stock_p, 0 );

    calc_delta_weight( my_portfolio, stock_p, stock_i, 0 );

    cash += 2,500,000;
    optimize_portfolio( my_portfolio, stock_p, stock_i, 1, cash );

    cash += 2,500,000;
    optimize_portfolio( my_portfolio, stock_p, stock_i, 2, cash );
	
    return 0;
}
