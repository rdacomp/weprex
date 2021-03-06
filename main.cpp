/****************************************************************************

  This file is part of the Webstella protocols exchange (Weprex) software.

  Copyright (C) 2018 Oleg Malyavkin.
  Contact: weprexsoft@gmail.com

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.

****************************************************************************/

#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QtCore>
#include <QApplication>
#include <QSplashScreen>

#include "wsqmlapplication.h"
#include "interfaces/wssocketinterface.h"
#include "protocols/wsmodbusparameter.h"
#include "protocols/wsparametershash.h"
#include "protocols/wsmodbustcpprotocol.h"
#include "timechart/timechart.h"
#include "utils/wssettings.h"
#include "utils/wsfile.h"
#include "conf.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	QPixmap pixmap(":/icon/splash.jpg");
	QSplashScreen splash(pixmap);
	QString splashText = WSQMLApplication::name() + " " + WSQMLApplication::version() + "\n" +
			"Build " + WSQMLApplication::build() + "\n" +
			WSQMLApplication::license() + "\n\n" +
			WSQMLApplication::copyrights() + "\n" +
			WSQMLApplication::additionalInfo() + "\n\n\n";
	splash.showMessage(splashText, Qt::AlignHCenter | Qt::AlignBottom, Qt::white);
	splash.show();
	app.processEvents();
	qDebug() << Conf::storeSettingsPath();
	
	qmlRegisterType<WSQMLApplication>("ru.webstella.weprex", 1, 0, "App");
	qmlRegisterType<webstella::gui::TimeChart>("ru.webstella.gui.chart", 1, 0, "TimeChart");
	qmlRegisterType<webstella::gui::TimeSeries>("ru.webstella.gui.chart", 1, 0, "TimeSeries");

	qRegisterMetaType<WSSettings*>("StoreSettings*");
	qRegisterMetaType<WSFile*>("File*");
	qRegisterMetaType<webstella::gui::TimeSeries*>("TimeSeries*");
	qRegisterMetaType<webstella::gui::TimeValue*>("TimeValue*");
	qRegisterMetaType<webstella::gui::IntTimeValue*>("IntTimeValue*");
	qRegisterMetaType<webstella::gui::DoubleTimeValue*>("DoubleTimeValue*");
	qRegisterMetaType<webstella::gui::BoolTimeValue*>("BoolTimeValue*");
	qRegisterMetaType<webstella::gui::InterpolateTimeValue>("InterpolateTimeValue");
	qRegisterMetaType<webstella::gui::TimeBounds>("TimeBounds");

	QQuickStyle::setStyle("Material");
	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;
	splash.close();
	return app.exec();
}
