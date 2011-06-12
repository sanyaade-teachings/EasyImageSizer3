/* (C) 2011 FalseCAM
 This file is part of EasyImageSizer.

 EasyImageSizer is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 any later version.

 EasyImageSizer is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with EasyImageSizer.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "easyimagesizer3/eisimage.h"
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QProcess>

EisImage::EisImage() {
}

EisImage::EisImage(QString file, int index = 0) {
	this->file = file;
	this->name = QFileInfo(file).baseName();
	this->image = QImage(file);
	this->index = index;
	readMetadata();
}

EisImage::~EisImage() {

}

void EisImage::readMetadata() {
}

void EisImage::setImage(QImage img) {
	this->image = img;
}

QImage EisImage::getImage() {
	return this->image;
}

void EisImage::setName(QString name) {
	this->name = name;
}

QString EisImage::getName() {
	return name;
}

int EisImage::getIndex() {
	return index;
}

QString EisImage::getOriginalFile() {
	return this->file;
}

/*
 Saves image to given folder in given format and quality.
 */
QString EisImage::save(QString folder, QString format, int quality) {
	QString filename = folder + "/" + name + "." + format;
	qDebug("[EisImage] Filename is %s, Format is %s", qPrintable(filename),
			qPrintable(format));
	if (!this->image.save(filename, qPrintable(format), quality)) {
		qDebug("[EisImage] %s could not been saved.", qPrintable(filename));
	} else {
		copyExifData(this->file, filename);
	}
	return filename;
}

/*
 Saves image to currents folder subfolder "eis" in given format and quality.
 */
QString EisImage::save(QString format, int quality) {
	QString folder = QFileInfo(file).absolutePath() + "/eis";
	if (!QDir(folder).exists())
		QDir().mkdir(QDir(folder).path());
	return save(folder, format, quality);
}

// Copy exif Data from one file to another
void EisImage::copyExifData(QString srcFile, QString destFile) {
	// Start new Process that copies exif data
	QProcess process;
	process.start(
			QString("exiftool -all= -overwrite_original -tagsfromfile \"").append(
					srcFile) .append("\" -exif:all \"").append(destFile).append(
					"\"").replace("/", QDir::separator()));
	// Wait until process finished
	process.waitForFinished();
}