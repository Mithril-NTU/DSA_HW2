//
//  main.cpp
//  HW2_2_4
//
//  Created by mithril on 15/4/12.
//  Copyright (c) 2015年 mithril. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <map>
#include <vector>
#include <sstream>
using namespace std;

struct Info{
    unsigned Click;
    unsigned Impression;
    string DisplayID;
    unsigned AdvertiserID;
    unsigned KeywordID;
    unsigned TitleID;
    unsigned DescriptionID;
    unsigned Depth;
    unsigned Position;
    unsigned QueryID;
};

void show_svec(vector<string> &vec){
    vector<string>::iterator m;
    for (m = vec.begin(); m != vec.end(); m++) {
        cout<<*m;
    }
}

void my_get(unsigned u, unsigned a, unsigned q, unsigned p, unsigned d, vector<multimap<unsigned, Info> > &data){
    multimap<unsigned, Info>::iterator beg, fin, m;
    vector<string> output;
    beg = data[u].lower_bound(a);
    fin = data[u].upper_bound(a);
    stringstream ss;
    cout<<"********************\n";
    for (m = beg; m != fin; m++) {
        if (m->second.Depth == d && m->second.Position == p && m->second.QueryID == q){
            ss<<m->second.Click<<"\t"<<m->second.Impression<<endl;
            output.push_back(ss.str());
            ss.str("");
        }
    }
    sort(output.begin(), output.end());
    vector<string>::iterator eraseit;
    eraseit = unique(output.begin(), output.end());
    output.erase(eraseit, output.end());
    show_svec(output);
    cout<<"********************\n";
}

void my_click(unsigned u, vector<multimap<unsigned, Info> > &data){
    multimap<unsigned, Info>::iterator m;
    vector<string> output;
    stringstream ss;
    cout<<"********************\n";
    for (m = data[u].begin(); m != data[u].end(); m++){
        if (m->second.Click > 0) {
            ss<<m->first<<" "<<m->second.QueryID<<endl;
            output.push_back(ss.str());
            ss.str("");
        }
    }
    sort(output.begin(), output.end());
    vector<string>::iterator eraseit;
    eraseit = unique(output.begin(), output.end());
    output.erase(eraseit, output.end());
    show_svec(output);
    cout<<"********************\n";
}

//string my_show(unsigned u, unsigned a, vector<multimap<unsigned, Info> > &data){
//    multimap<unsigned, Info>::iterator beg, fin, m;
//    beg = data[u].lower_bound(a);
//    fin = data[u].upper_bound(a);
//    vector<string> tmp;
//    string output;
//    for (m = beg; m != fin; m++) {
//        stringstream ss;
//        ss<<"\t"<<m->second.DisplayID<<" "<<m->second.AdvertiserID<<" "<<m->second.KeywordID<<" "<<m->second.TitleID<<" "<<m->second.DescriptionID<<endl;
//        tmp.push_back(ss.str());
//    }
//    vector<string>::iterator eraseit, k;
//    eraseit = unique(tmp.begin(), tmp.end());
//    tmp.erase(eraseit, tmp.end());
//    for (k = tmp.begin(); k != tmp.end();k++){
//        output += *k;
//    }
//    return output;
//}

void my_impression(unsigned u1, unsigned u2, vector<multimap<unsigned, Info> > &data){
    multimap<unsigned, Info>::iterator m, n, k, l;
    vector<unsigned> tmp;
    vector<string> output;
    cout<<"********************\n";
    for (m = data[u1].begin(); m != data[u1].end(); m++){
        for (n = data[u2].lower_bound(m->first); n != data[u2].upper_bound(m->first); n++) {
            if ((m->second.Impression > 0) && (n->second.Impression > 0)) {
                tmp.push_back(m->first);
            }
        }
    }
    vector<unsigned>::iterator er;
    sort(tmp.begin(), tmp.end());
    er = unique(tmp.begin(), tmp.end());
    tmp.erase(er, tmp.end());
    
    vector<string>::iterator eraseit;
    vector<unsigned>::iterator itr;
    stringstream ss;
    for (itr = tmp.begin(); itr != tmp.end(); itr++) {
        output.erase(output.begin(), output.end());
        cout<<*itr<<endl;
        output.push_back(ss.str());
        for (k = data[u1].lower_bound(*itr); k != data[u1].upper_bound(*itr); k++) {
            ss<<"\t"<<k->second.DisplayID<<" "<<k->second.AdvertiserID<<" "<<k->second.KeywordID<<" "<<k->second.TitleID<<" "<<k->second.DescriptionID<<endl;
            output.push_back(ss.str());
            ss.str("");
        }
        for (l = data[u2].lower_bound(*itr); l != data[u2].upper_bound(*itr); l++) {
            ss<<"\t"<<l->second.DisplayID<<" "<<l->second.AdvertiserID<<" "<<l->second.KeywordID<<" "<<l->second.TitleID<<" "<<l->second.DescriptionID<<endl;
            output.push_back(ss.str());
            ss.str("");
        }
        sort(output.begin(), output.end());
        eraseit = unique(output.begin(), output.end());
        output.erase(eraseit, output.end());
        show_svec(output);
    }
    cout<<"********************\n";
}

void my_profit(unsigned a, double theta, multimap<unsigned, unsigned> &ad_to_useid, vector<multimap<unsigned, Info> > &data){
    vector<unsigned> result;
    multimap<unsigned, unsigned>::iterator beg1, fin1, m1;
    multimap<unsigned, Info>::iterator beg2, fin2, m2;
    beg1 = ad_to_useid.lower_bound(a);
    fin1 = ad_to_useid.upper_bound(a);
    unsigned u;
    cout<<"********************\n";
    
    for (m1 = beg1; m1 != fin1; m1++) {
        u = m1->second;
        beg2 = data[u].lower_bound(a);
        fin2 = data[u].upper_bound(a);
        for (m2 = beg2; m2 != fin2; m2++) {
            if (m2->second.Impression != 0) {
                if (double(m2->second.Click) / double(m2->second.Impression) >= theta) {
//                    cout<<u<<endl;
                    result.push_back(u);
                }
            }
            else {
                if (theta == 0) {
                    result.push_back(u);
                }
            }
        }
    }
    sort(result.begin(), result.end(), less<unsigned>() );
    vector<unsigned>::iterator iter, eraseit;
    eraseit = unique(result.begin(), result.end());
    result.erase(eraseit, result.end());
    
    for ( iter = result.begin() ; iter != result.end() ; iter++ )
    {
        cout<<*iter<<endl;
    }
    cout<<"********************\n";
}

void my_profit2(unsigned a, double theta, vector<multimap<unsigned, Info> > &data){
    vector<unsigned> result;
    vector<multimap<unsigned, Info> >::iterator itr;
    multimap<unsigned, Info>::iterator beg2, fin2, m2;
    int num = 0;
    cout<<"********************\n";
    for (itr = data.begin(); itr != data.end(); itr++, num++) {
        if (itr->count(a) > 0) {
            beg2 = itr->lower_bound(a);
            fin2 = itr->upper_bound(a);
            for (m2 = beg2; m2 != fin2; m2++) {
                if (m2->second.Impression != 0) {
                    if (double(m2->second.Click) / double(m2->second.Impression) >= theta) {
                    //                    cout<<u<<endl;
                        result.push_back(num);
                    }
                }
                else {
                    if (theta == 0) {
                        result.push_back(num);
                    }
                }
            }
        }
    }
    vector<unsigned>::iterator i;
    sort(result.begin(), result.end(), less<unsigned>() );
    vector<unsigned>::iterator eraseit;
    eraseit = unique(result.begin(), result.end());
    result.erase(eraseit, result.end());
    for ( i = result.begin() ; i != result.end() ; i++ )
    {
        cout<<*i<<endl;
    }
    cout<<"********************\n";
}



int main(int argc, const char * argv[]) {
    cout<<"Loading\n";
    multimap<unsigned, unsigned> ad_to_useid;
    vector<multimap<unsigned, Info> > data(30000000);
//    vector<unsigned> au(70000000);
    FILE* file;
//    file = fopen("/Users/mithril/Documents/DSA/HW2_2_4/HW2_2_4/kddcup2012track2.txt", "r");
//    file = fopen("/Users/mithril/Documents/DSA/HW2_2_4/HW2_2_4/sampledata.txt", "r");
//    file = fopen("/Users/mithril/Documents/DSA/HW2_2_4/HW2_2_4/demotrack.txt", "r");
    file = fopen(argv[1], "r");
    if (file == NULL){
        cout<<"Open file failed!"<<endl;
        return 0;
    }
    
    char* buffer = new char[100];
//    int count = 0;
    char* tmp;
    char* per_line_data[12];
    int i = 0;
    Info tmp_info;
    unsigned AdID;
    unsigned UserID;
    
    while (fgets(buffer, 100, file) != NULL) {
        i = 0;
        tmp = strtok(buffer, "\t");
        while (tmp != NULL){
//            cout<<tmp<<endl;
            per_line_data[i] = tmp;
            tmp = strtok(NULL, " \t\n");
            i++;
        }
        AdID = atoi(per_line_data[3]);
        UserID = atoi(per_line_data[11]);
        
        tmp_info.Depth = atoi(per_line_data[5]);
        tmp_info.Position = atoi(per_line_data[6]);
        tmp_info.QueryID = atoi(per_line_data[7]);
        tmp_info.Click = atoi(per_line_data[0]);
        tmp_info.Impression = atoi(per_line_data[1]);
        tmp_info.DisplayID = per_line_data[2];
        tmp_info.AdvertiserID = atoi(per_line_data[4]);
        tmp_info.KeywordID = atoi(per_line_data[8]);
        tmp_info.TitleID = atoi(per_line_data[9]);
        tmp_info.DescriptionID = atoi(per_line_data[10]);
        
//        if (ad_to_useid.find(AdID) == ad_to_useid.end()) {
//            ad_to_useid.insert(make_pair(AdID, UserID));
//        }
//        else{
//            multimap<unsigned, unsigned>::iterator t_beg, t_fin, t_m;
//            t_beg = ad_to_useid.lower_bound(AdID);
//            t_fin = ad_to_useid.upper_bound(AdID);
//            bool in = true;
//            for (t_m = t_beg; t_m != t_fin; t_m++) {
//                if (t_m->second == UserID) {
//                    in = false;
//                    break;
//                }
//            }
//            if (in) {
//                ad_to_useid.insert(make_pair(AdID, UserID));
//            }
//        }
//        ad_to_useid.insert(make_pair(AdID, UserID));
        data[UserID].insert(make_pair(AdID, tmp_info));

    }
    fclose(file);
    delete buffer;
    
  //  multimap<unsigned, Info>::iterator f_itr;
    //for (f_itr = data[490234].begin(); f_itr != data[490234].end(); f_itr++) {
      //  cout<<f_itr->second.Click<<" "<<f_itr->second.Impression<<" "<<f_itr->second.DisplayID<<" "<<f_itr->first<<" "<<f_itr->second.AdvertiserID<<" "<<f_itr->second.Depth<<" "<<f_itr->second.Position<<" "<<f_itr->second.QueryID<<" "<<f_itr->second.KeywordID<<" "<<f_itr->second.TitleID<<" "<<f_itr->second.DescriptionID<<" "<<"490234\n";
    //}
//
//    my_click(12565, data);
//    my_get(6231937, 21459920, 2416, 2, 2, data);
////    my_profit(21560664, 0, ad_to_useid, data);
//    my_profit2(21459920, 0.1, data);
//    my_impression(6231938, 0, data);
    
    string a;
    string i_get("get");
    string i_clicked("clicked");
    string i_profit("profit");
    string i_impressed("impressed");
    string i_quit("quit");
    unsigned params[5] = {0};
    cout<<"Please input:\n";
    while (true){
        cin>>a;
        if (a == i_clicked) {
            cin>>params[0];
            my_click(params[0], data);
        }
        else if (a == i_get){
            cin>>params[0];
            cin>>params[1];
            cin>>params[2];
            cin>>params[3];
            cin>>params[4];
            my_get(params[0], params[1], params[2], params[3], params[4], data);
        }
        else if (a == i_profit){
            cin>>params[0];
            cin>>params[1];
            my_profit2(params[0], params[1], data);
        }
        else if (a == i_impressed){
            cin>>params[0];
            cin>>params[1];
            my_impression(params[0], params[1], data);
        }
        else if (a == i_quit){
            return 0;
        }
//        else{
//            cout<<"Wrong Input\n";
//            return -1;
//        }
    }
    
    return 0;
}
