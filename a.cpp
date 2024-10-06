#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string recipeName;
string fileName;

// BOMを追加する関数
void writeBOM(ofstream& outputfile) {
    const char BOM[] = { (char)0xEF, (char)0xBB, (char)0xBF };
    outputfile.write(BOM, sizeof(BOM));
}

// 最初からh1前まで出力
void writeHead(ofstream& outputfile) {
    outputfile << "{% extends \"layout.html\" %}" << endl
        << "{% block title %}<title>recipes</title>{% endblock %}" << endl
        << "{% block content %}"<<endl
        << "<div class=\"container\">" << endl
        << "\t<header class=\"d-flex flex-wrap justify-content-center py-3 mb-4 border-bottom\">" << endl
        << "\t\t<a href=\"/\" class=\"d-flex align-items-center mb-3 mb-md-0 me-md-auto link-body-emphasis text-decoration-none\">" << endl
        << "\t\t\t<svg class=\"bi me-2\" width=\"40\" height=\"32\"><use xlink:href=\"#bootstrap\"/></svg>" << endl
        << "\t\t\t<span class=\"fs-4\">レシピwithタイマー</span>" << endl
        << "\t\t</a>" << endl
        << "\t\t<ul class=\"nav nav-pills\">" << endl
        << "\t\t\t<li class=\"nav-item\"><a href=\"#\" class=\"nav-link active\" aria-current=\"page\">Home</a></li>" << endl
        << "\t\t\t<li class=\"nav-item\"><a href=\"#\" class=\"nav-link\">recipes</a></li>" << endl
        << "\t\t\t<li class=\"nav-item\"><a href=\"#\" class=\"nav-link\">FAQs</a></li>" << endl
        << "\t\t\t<li class=\"nav-item\"><a href=\"#\" class=\"nav-link\">contacts</a></li>" << endl
        << "\t\t\t<li class=\"nav-item\"><a href=\"#\" class=\"nav-link\">About</a></li>" << endl
        << "\t\t</ul>" << endl
        << "\t</header>" << endl
        << "</div>" << endl;
}

// 画像部分を出力
void writeImage(ofstream& outputfile, const string& imageFile) {
    outputfile << "\t\t<img src=\"{ { url_for('static', filename = 'img/" + imageFile + "') }}\" alt=\"" + recipeName + "\">" << endl;
}

// h1から<p>材料</p>まで出力
void writeH1(ofstream& outputfile,const string mainImage) {
    outputfile << "\t\t<h1>" << recipeName << "</h1>" << endl;
    writeImage(outputfile, mainImage);
    outputfile << "\t\t<p>材料</p>" << endl;
}

// タイマー部分を出力
void writeTimer(ofstream& outputfile, const string& time) {
    outputfile << "\t\t<div id=\"container\">" << endl
        << "\t\t\t<div id=\"time\" value=\"" + time + "\" >時間を測るためにstartを押してね</div>" << endl
        << "\t\t\t<div id=\"buttons\">" << endl
        << "\t\t\t\t<input id=\"start\" type=\"button\" value=\"start\">" << endl
        << "\t\t\t\t<input id=\"stop\" type=\"button\" value=\"stop\">" << endl
        << "\t\t\t\t<input id=\"reset\" type=\"button\" value=\"reset\">" << endl
        << "\t\t\t</div>" << endl
        << "\t\t</div>" << endl;
}

// 材料部分を出力
void writeIngredient(ofstream& outputfile, const string& text) {
    outputfile << "\t\t<p class=\"zairyou\">" << text << "</p>" << endl;
}

// 作り方部分を出力
void writeMake(ofstream& outputfile, const string& text) {
    outputfile << "\t\t<p class=\"make\">" << text << "</p>" << endl;
}

// テキスト部分を出力(予備)
void writeText(ofstream& outputfile, const string& text) {
    outputfile << "\t\t<p>" << text << "</p>" << endl;
}

// h2と<div class="recipe">までの出力
void writeH2(ofstream& outputfile) {
    outputfile << "\t\t<p>作り方</p>" << endl
        << "\t\t<div class=\"recipe\">" << endl;
}

// </div> <p>完成!</p>から最後まで出力
void writeEnd(ofstream& outputfile) {
    outputfile << "\t\t</div>" << endl
        << "\t\t<p>完成!</p>" << endl
        << "{% endblock %}" << endl;
}

int main(void) {
    // レシピ名(ファイル名取得)
    //cout << "レシピ名を入力してください([.]を使用しない): " << endl;
    getline(cin, recipeName);  // cinではなくgetlineで入力を取得
    fileName = "testapp/templates/testapp/"+recipeName + ".html";

    ofstream outputfile(fileName, ios::out | ios::binary);
    if (!outputfile) {
        cerr << "ファイルの作成に失敗しました。" << endl;
        return 1;
    }

    writeBOM(outputfile); // BOMを書き込む
    writeHead(outputfile);
    const string mainImage = "calbo.png";
    writeH1(outputfile,mainImage);//

    // 材料取得
    string str;
    //cout << "材料を入力してください(材料はスペース区切りで入力 @imageで画像 @endで入力終了): " << endl;
    while (true) {
        cin >> str;
        if (str == "@end") {
            break;
        }
        else if (str == "@image") {
            string imageFile;
            cin >> imageFile;
            writeImage(outputfile, imageFile);
        }
        else {
            string amount;
            cin >> amount;
            str += " " + amount;
            writeIngredient(outputfile, str);
        }
    }

    writeH2(outputfile);

    // 作り方取得
    //cout << "作り方を入力してください @imageで画像 @timerでタイマー @endで入力終了): " << endl;
    while (true) {
        cin >> str;
        if (str == "@end") {
            break;
        }
        else if (str == "@image") {
            string imageFile;
            cin >> imageFile;
            writeImage(outputfile, imageFile);
        }
        else if (str == "@timer") {
            string time;
            cin >> time;
            writeTimer(outputfile, time);
        }
        else {
            writeMake(outputfile, str);
        }
    }

    writeEnd(outputfile);
    outputfile.close();

    return 0;
}