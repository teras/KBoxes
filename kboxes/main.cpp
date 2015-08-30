/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Πεμ Ιαν 20 17:36:13 EET 2000
    copyright            : (C) 2000 by Panos Katsaloulis
    email                : teras@writeme.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <qapplication.h>
#include <qfont.h>

#include "kboxes.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  a.setFont(QFont("helvetica", 12));
  /* uncomment the following line, if you want a Windows 95 look*/

  KBoxes *kboxes=new KBoxes();
  a.setMainWidget(kboxes);

  kboxes->setCaption("Boxes !");
  kboxes->show();

  return a.exec();
}
