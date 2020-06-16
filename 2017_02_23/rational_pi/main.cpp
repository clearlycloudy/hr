#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
#include <map>
#include <utility>

using namespace std;

double pi = 3.1415926535897932384626433832795028841971693993751;


double get_error( long top, long bot ){
    return abs((double)top/bot - pi);
}

double get_best_from_range( long start, long end, long & top, long & bot ){
    double error = std::numeric_limits<double>::max();
    double n = start;
    while (n <= end ){
    	double d_numer = pi * n;
    	long numer = (long) d_numer;
    	long numer_ceil = numer + 1;
    	double err1 = abs((double)numer/n - pi);
    	double err2 = abs((double)numer_ceil/n - pi);
    	if( err1 < err2 ){
    	    if( error > err1 ){
    		error = err1;
    		bot = n;
    		top = numer;
    	    }
    	}else{
    	    if( error > err2 ){
    		error = err2;
    		bot = n;
    		top = numer_ceil;
    	    }
    	}
    	n = n + 1;
    }
    return error;
}

int main() {

    map<long,pair<long,long> > lookup;
    lookup[1] = pair<long,long>(3,1);
    lookup[4] = pair<long,long>(13,4);
    lookup[5] = pair<long,long>(16,5);
    lookup[6] = pair<long,long>(19,6);
    lookup[7] = pair<long,long>(22,7);
    lookup[57] = pair<long,long>(179,57);
    lookup[64] = pair<long,long>(201,64);
    lookup[71] = pair<long,long>(223,71);
    lookup[78] = pair<long,long>(245,78);
    lookup[85] = pair<long,long>(267,85);
    lookup[92] = pair<long,long>(289,92);
    lookup[99] = pair<long,long>(311,99);
    lookup[106] = pair<long,long>(333,106);
    lookup[113] = pair<long,long>(355,113);
    lookup[16604] = pair<long,long>(52163,16604);
    lookup[16717] = pair<long,long>(52518,16717);
    lookup[16830] = pair<long,long>(52873,16830);
    lookup[16943] = pair<long,long>(53228,16943);
    lookup[17056] = pair<long,long>(53583,17056);
    lookup[17169] = pair<long,long>(53938,17169);
    lookup[17282] = pair<long,long>(54293,17282);
    lookup[17395] = pair<long,long>(54648,17395);
    lookup[17508] = pair<long,long>(55003,17508);
    lookup[17621] = pair<long,long>(55358,17621);
    lookup[17734] = pair<long,long>(55713,17734);
    lookup[17847] = pair<long,long>(56068,17847);
    lookup[17960] = pair<long,long>(56423,17960);
    lookup[18073] = pair<long,long>(56778,18073);
    lookup[18186] = pair<long,long>(57133,18186);
    lookup[18299] = pair<long,long>(57488,18299);
    lookup[18412] = pair<long,long>(57843,18412);
    lookup[18525] = pair<long,long>(58198,18525);
    lookup[18638] = pair<long,long>(58553,18638);
    lookup[18751] = pair<long,long>(58908,18751);
    lookup[18864] = pair<long,long>(59263,18864);
    lookup[18977] = pair<long,long>(59618,18977);
    lookup[19090] = pair<long,long>(59973,19090);
    lookup[19203] = pair<long,long>(60328,19203);
    lookup[19316] = pair<long,long>(60683,19316);
    lookup[19429] = pair<long,long>(61038,19429);
    lookup[19542] = pair<long,long>(61393,19542);
    lookup[19655] = pair<long,long>(61748,19655);
    lookup[19768] = pair<long,long>(62103,19768);
    lookup[19881] = pair<long,long>(62458,19881);
    lookup[19994] = pair<long,long>(62813,19994);
    lookup[20107] = pair<long,long>(63168,20107);
    lookup[20220] = pair<long,long>(63523,20220);
    lookup[20333] = pair<long,long>(63878,20333);
    lookup[20446] = pair<long,long>(64233,20446);
    lookup[20559] = pair<long,long>(64588,20559);
    lookup[20672] = pair<long,long>(64943,20672);
    lookup[20785] = pair<long,long>(65298,20785);
    lookup[20898] = pair<long,long>(65653,20898);
    lookup[21011] = pair<long,long>(66008,21011);
    lookup[21124] = pair<long,long>(66363,21124);
    lookup[21237] = pair<long,long>(66718,21237);
    lookup[21350] = pair<long,long>(67073,21350);
    lookup[21463] = pair<long,long>(67428,21463);
    lookup[21576] = pair<long,long>(67783,21576);
    lookup[21689] = pair<long,long>(68138,21689);
    lookup[21802] = pair<long,long>(68493,21802);
    lookup[21915] = pair<long,long>(68848,21915);
    lookup[22028] = pair<long,long>(69203,22028);
    lookup[22141] = pair<long,long>(69558,22141);
    lookup[22254] = pair<long,long>(69913,22254);
    lookup[22367] = pair<long,long>(70268,22367);
    lookup[22480] = pair<long,long>(70623,22480);
    lookup[22593] = pair<long,long>(70978,22593);
    lookup[22706] = pair<long,long>(71333,22706);
    lookup[22819] = pair<long,long>(71688,22819);
    lookup[22932] = pair<long,long>(72043,22932);
    lookup[23045] = pair<long,long>(72398,23045);
    lookup[23158] = pair<long,long>(72753,23158);
    lookup[23271] = pair<long,long>(73108,23271);
    lookup[23384] = pair<long,long>(73463,23384);
    lookup[23497] = pair<long,long>(73818,23497);
    lookup[23610] = pair<long,long>(74173,23610);
    lookup[23723] = pair<long,long>(74528,23723);
    lookup[23836] = pair<long,long>(74883,23836);
    lookup[23949] = pair<long,long>(75238,23949);
    lookup[24062] = pair<long,long>(75593,24062);
    lookup[24175] = pair<long,long>(75948,24175);
    lookup[24288] = pair<long,long>(76303,24288);
    lookup[24401] = pair<long,long>(76658,24401);
    lookup[24514] = pair<long,long>(77013,24514);
    lookup[24627] = pair<long,long>(77368,24627);
    lookup[24740] = pair<long,long>(77723,24740);
    lookup[24853] = pair<long,long>(78078,24853);
    lookup[24966] = pair<long,long>(78433,24966);
    lookup[25079] = pair<long,long>(78788,25079);
    lookup[25192] = pair<long,long>(79143,25192);
    lookup[25305] = pair<long,long>(79498,25305);
    lookup[25418] = pair<long,long>(79853,25418);
    lookup[25531] = pair<long,long>(80208,25531);
    lookup[25644] = pair<long,long>(80563,25644);
    lookup[25757] = pair<long,long>(80918,25757);
    lookup[25870] = pair<long,long>(81273,25870);
    lookup[25983] = pair<long,long>(81628,25983);
    lookup[26096] = pair<long,long>(81983,26096);
    lookup[26209] = pair<long,long>(82338,26209);
    lookup[26322] = pair<long,long>(82693,26322);
    lookup[26435] = pair<long,long>(83048,26435);
    lookup[26548] = pair<long,long>(83403,26548);
    lookup[26661] = pair<long,long>(83758,26661);
    lookup[26774] = pair<long,long>(84113,26774);
    lookup[26887] = pair<long,long>(84468,26887);
    lookup[27000] = pair<long,long>(84823,27000);
    lookup[27113] = pair<long,long>(85178,27113);
    lookup[27226] = pair<long,long>(85533,27226);
    lookup[27339] = pair<long,long>(85888,27339);
    lookup[27452] = pair<long,long>(86243,27452);
    lookup[27565] = pair<long,long>(86598,27565);
    lookup[27678] = pair<long,long>(86953,27678);
    lookup[27791] = pair<long,long>(87308,27791);
    lookup[27904] = pair<long,long>(87663,27904);
    lookup[28017] = pair<long,long>(88018,28017);
    lookup[28130] = pair<long,long>(88373,28130);
    lookup[28243] = pair<long,long>(88728,28243);
    lookup[28356] = pair<long,long>(89083,28356);
    lookup[28469] = pair<long,long>(89438,28469);
    lookup[28582] = pair<long,long>(89793,28582);
    lookup[28695] = pair<long,long>(90148,28695);
    lookup[28808] = pair<long,long>(90503,28808);
    lookup[28921] = pair<long,long>(90858,28921);
    lookup[29034] = pair<long,long>(91213,29034);
    lookup[29147] = pair<long,long>(91568,29147);
    lookup[29260] = pair<long,long>(91923,29260);
    lookup[29373] = pair<long,long>(92278,29373);
    lookup[29486] = pair<long,long>(92633,29486);
    lookup[29599] = pair<long,long>(92988,29599);
    lookup[29712] = pair<long,long>(93343,29712);
    lookup[29825] = pair<long,long>(93698,29825);
    lookup[29938] = pair<long,long>(94053,29938);
    lookup[30051] = pair<long,long>(94408,30051);
    lookup[30164] = pair<long,long>(94763,30164);
    lookup[30277] = pair<long,long>(95118,30277);
    lookup[30390] = pair<long,long>(95473,30390);
    lookup[30503] = pair<long,long>(95828,30503);
    lookup[30616] = pair<long,long>(96183,30616);
    lookup[30729] = pair<long,long>(96538,30729);
    lookup[30842] = pair<long,long>(96893,30842);
    lookup[30955] = pair<long,long>(97248,30955);
    lookup[31068] = pair<long,long>(97603,31068);
    lookup[31181] = pair<long,long>(97958,31181);
    lookup[31294] = pair<long,long>(98313,31294);
    lookup[31407] = pair<long,long>(98668,31407);
    lookup[31520] = pair<long,long>(99023,31520);
    lookup[31633] = pair<long,long>(99378,31633);
    lookup[31746] = pair<long,long>(99733,31746);
    lookup[31859] = pair<long,long>(100088,31859);
    lookup[31972] = pair<long,long>(100443,31972);
    lookup[32085] = pair<long,long>(100798,32085);
    lookup[32198] = pair<long,long>(101153,32198);
    lookup[32311] = pair<long,long>(101508,32311);
    lookup[32424] = pair<long,long>(101863,32424);
    lookup[32537] = pair<long,long>(102218,32537);
    lookup[32650] = pair<long,long>(102573,32650);
    lookup[32763] = pair<long,long>(102928,32763);
    lookup[32876] = pair<long,long>(103283,32876);
    lookup[32989] = pair<long,long>(103638,32989);
    lookup[33102] = pair<long,long>(103993,33102);
    lookup[33215] = pair<long,long>(104348,33215);
    lookup[66317] = pair<long,long>(208341,66317);
    lookup[99532] = pair<long,long>(312689,99532);
    lookup[265381] = pair<long,long>(833719,265381);
    lookup[364913] = pair<long,long>(1146408,364913);
    lookup[995207] = pair<long,long>(3126535,995207);
    lookup[1.36012e+06] = pair<long,long>(4272943,1360120);
    lookup[1.72503e+06] = pair<long,long>(5419351,1725033);
    lookup[1.34354e+07] = pair<long,long>(42208400,13435351);
    lookup[1.51604e+07] = pair<long,long>(47627751,15160384);
    lookup[1.68854e+07] = pair<long,long>(53047102,16885417);
    lookup[1.86104e+07] = pair<long,long>(58466453,18610450);
    lookup[2.03355e+07] = pair<long,long>(63885804,20335483);
    lookup[2.20605e+07] = pair<long,long>(69305155,22060516);
    lookup[2.37855e+07] = pair<long,long>(74724506,23785549);
    lookup[2.55106e+07] = pair<long,long>(80143857,25510582);
    lookup[7.82568e+07] = pair<long,long>(245850922,78256779);

    //loookup obtained from continued fraction approximation of pi
    lookup[260280919e+00] = pair<long,long>(817696623,260280919);
    lookup[6064717916e+00] = pair<long,long>(19052873251,6064717916);
    lookup[6324998835e+00] = pair<long,long>(19870569874,6324998835);
    lookup[12389716751e+00] = pair<long,long>(38923443125,12389716751);
    lookup[93053016092e+00] = pair<long,long>(292334671749,93053016092);
    lookup[384601781119e+00] = pair<long,long>(1208262130121,384601781119);
    lookup[13554115355257e+00] = pair<long,long>(42581509225984,13554115355257);
    lookup[13938717136376e+00] = pair<long,long>(43789771356105,13938717136376);
    lookup[27492832491633e+00] = pair<long,long>(86371280582089,27492832491633);
    lookup[41431549628009e+00] = pair<long,long>(130161051938194,41431549628009);
    lookup[110355931747651e+00] = pair<long,long>(346693384458477,110355931747651);
    lookup[372499344870962e+00] = pair<long,long>(1170241205313625,372499344870962);
	
    long min,max;
    cin >> min >> max;
    long top1;
    long bot1;
    double error1 = std::numeric_limits<double>::max();
    
    auto it = lookup.lower_bound( min );
    auto it_e = lookup.lower_bound( max );
    
    if( it->first > min ){
	if( it->first > max ){
	    if( max - min < 1e7 ){
		error1 = get_best_from_range( min, max, top1, bot1 );
	    }else{
		error1 = get_best_from_range( max-1e7, max, top1, bot1 );
	    }
	}
    }

    long top2;
    long bot2;
    double error2 = std::numeric_limits<double>::max();
    auto it_best = it_e;
    while( it != lookup.end() && it_best != it ){
	if( it_best == lookup.end() ){
	    --it_best;
	    continue;
	}
	if( it_best->first <= max ){
	    top2 = it_best->second.first;
	    bot2 = it_best->second.second;
	    error2 = get_error( top2, bot2 );
	    break;
	}
	it_best--;
    }

    long top3;
    long bot3;
    double error3 = std::numeric_limits<double>::max();
    // if( it != lookup.end() && it_best != lookup.end() && it_best->first < max ){
    // 	if( it_best->first < 1e7 ){
    // 	    error3 = get_best_from_range( it_best->first, max, top3, bot3 );
    // 	}
    // }

    map<double, pair<long,long> > rank;
    rank[error1] = pair<long,long>(top1,bot1);
    rank[error2] = pair<long,long>(top2,bot2);
    // rank[error3] = pair<long,long>(top3,bot3);

    long top, bot;
    top = rank.begin()->second.first;
    bot = rank.begin()->second.second;
    cout << top <<"/" << bot << endl;
    return 0;
}
