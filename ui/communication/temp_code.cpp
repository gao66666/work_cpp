// void Widget::paintEvent(QPaintEvent *event)
// {
//     Q_UNUSED(event);

//     QPainter painter;
//     painter.begin(this);

//     painter.setRenderHints(QPainter::Antialiasing,true);
//     QPixmap pixmap(":/src_pic/QQ.jpg");
//     QPainterPath path;
//     path.addEllipse(140,50,90,90);//加入一个圆形   绘图是从左上角的（56，20）坐标开始绘制的  ，120，120是绘图的宽高
//     painter.setClipPath(path);
//     painter.drawPixmap(QRect(140,50,90,90),pixmap);
//     painter.end();
// }
//
// void Widget::on_pushButton_clicked()
// {
//     chat_widget = new chat;
//     this->hide();
//     chat_widget->show();

// }
