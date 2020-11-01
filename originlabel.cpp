#include "originlabel.h"

OriginLabel::OriginLabel(int *originX,int *originY):QLabel(){
    this->originX = originX;
    this->originY = originY;

    this->setMinimumSize(QSize(960,616));
}
OriginLabel::~OriginLabel(){

}

void OriginLabel::mousePressEvent(QMouseEvent *event){
    // Update the origin coordinates
   // *(this->originX) = event->x();
    //*(this->originY) = event->y();

    int x = event->x();
    int y = event->y();

    *(this->originX) = x;
    *(this->originY) = y;
    std::cout<<x<<std::endl;
    std::cout<<y<<std::endl;


    // Open the file
    QFile file_obj("./params.json");
    if(!file_obj.open(QIODevice::ReadOnly)){
      std::cout<<"Failed to open ./params.json"<<std::endl;
      exit(1);
    }

    // Retrieve the json file
    QTextStream file_text(&file_obj);
    QString json_string;
    json_string = file_text.readAll();
    file_obj.close();

    // Write the new data
    QByteArray json_bytes = json_string.toLocal8Bit();
    auto json_doc = QJsonDocument::fromJson(json_bytes);
    auto json_obj = json_doc.object();
    json_obj["originX"] = *(this->originX);
    json_obj["originY"] = *(this->originY);

    // Parse the object to bytes
    QJsonDocument json_doc_after(json_obj);
    json_string = json_doc_after.toJson();

    // Save the new json to file
    QFile save_file("./params.json");
    if(!save_file.open(QIODevice::WriteOnly)){
      std::cout<<"Failed to open ./params.json"<<std::endl;
      exit(1);
    }
    save_file.write(json_string.toLocal8Bit());
    save_file.close();
}
