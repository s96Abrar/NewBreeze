/*
	*
	* NBDeviceInfo.hpp - NBDeviceInfo.cpp class for NewBreeze
	*
*/

#pragma once

#include <fstream>
#include <unistd.h>

#include <QtCore>

#include <QVolumeInfo.hpp>

class NBDeviceManager;

class NBDeviceInfo {

	friend NBDeviceManager;

	public:
		NBDeviceInfo();
		NBDeviceInfo( const NBDeviceInfo& );

		QString driveName() const;
		QString driveLabel() const;
		QString driveFS() const;
		QString driveType() const;
		QString mountPoint() const;
		quint64 freeSpace() const;
		quint64 availSpace() const;
		quint64 usedSpace() const;
		quint64 driveSize() const;

	private:
		QString dN;			// Drive Name ( e.g, sda1, sda2, sr0, etc )
		QString dL;			// Drive Label ( e.g, Wheezy, Users, KeyDrive, etc )
		QString fS;			// Drive FileSystem ( e.g, ext2/3/4, fat32/vfat, ntfs, etc )
		QString dT;			// Drive Type ( HDD, USB, Optical, FUSE etc )
		QString mP;			// Mount Point
		quint64 fSz;		// Free Size
		quint64 aSz;		// Available Size
		quint64 uSz;		// Used Size
		quint64 dSz;		// Drive Size
};

Q_DECLARE_METATYPE(NBDeviceInfo);

class NBDeviceManager : public QObject {
	Q_OBJECT

	public :
		NBDeviceManager( QObject *parent = 0  );

		/* List of all mounted volumes: drives + vfs */
		static QList<NBDeviceInfo> allMounts();

		/* List of for all mounted drives */
		static QList<NBDeviceInfo> allDrives();

		/* List of all mounted vfs */
		static QList<NBDeviceInfo> allVirtualMounts();

		static NBDeviceInfo deviceInfoForPath( QString path );

	Q_SIGNALS :
		void updateDevices();
};