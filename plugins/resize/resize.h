/*
 EasyImageSizer - Resize

 EasyImageSizer plugin to Resize a QImage

 Copyright (C) 2010 - 2011 FalseCAM

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef RESIZE_H
#define RESIZE_H

#include "easyimagesizer3/easyimagesizer3plugin.h"
#include "easyimagesizer3/eisimage.h"

namespace Ui {
class Resize;
}

class Resize: public EasyImageSizer3Plugin {
Q_OBJECT
Q_INTERFACES(EasyImageSizer3Plugin)

public:
	Resize(QWidget *parent = 0);
	~Resize();
	QString getName();
	QString getTitle();
	QString getVersion();
	QString getAuthor();
	QString getDescription();
	QIcon getIcon();
	void convert(EisImage *image);

private slots:
	void changeSizePercentUse();
	void changeSizePixelUse();
	void changeSizePixel();
	void changeSizeRatio();

	void loadState();
	void saveState();

private:
	Ui::Resize *ui;

signals:
	void progress(int);
};

#endif // RESIZE_H