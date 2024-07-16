#pragma once

#include "config-dialog.hpp"
#include <obs.h>
#include <obs-frontend-api.h>
#include <QFrame>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>
#include <QString>

class OBSBasicSettings;

class MultistreamDock : public QFrame {
	Q_OBJECT

private:
	OBSBasicSettings *configDialog = nullptr;

	obs_data_t *current_config = nullptr;

	QVBoxLayout *mainCanvasLayout = nullptr;
	QVBoxLayout *mainCanvasOutputLayout = nullptr;
	QVBoxLayout *verticalCanvasLayout = nullptr;
	QVBoxLayout *verticalCanvasOutputLayout = nullptr;
	QPushButton *mainStreamButton = nullptr;
	QPushButton *configButton = nullptr;

	QString newer_version_available;

	QTimer videoCheckTimer;
	video_t *mainVideo = nullptr;
	std::vector<video_t *> oldVideo;

	std::map<std::string, obs_output_t *> outputs;

	void LoadSettingsFile();
	void LoadSettings();
	void LoadOutput(obs_data_t *data, bool vertical);
	void SaveSettings();

	bool StartOutput(obs_data_t *settings, QPushButton *streamButton);

	void outputButtonStyle(QPushButton *button);

	QIcon getPlatformFromEndpoint(QString endpoint);
	
	QIcon streamActiveIcon = QIcon(":/aitum/media/streaming.svg");
	QIcon streamInactiveIcon = QIcon(":/aitum/media/stream.svg");
	
	// Platform icons
	QIcon platformIconTwitch = QIcon(":/aitum/media/twitch.png");
	QIcon platformIconYouTube = QIcon(":/aitum/media/youtube.png");
	QIcon platformIconKick = QIcon(":/aitum/media/kick.png");
	QIcon platformIconTikTok = QIcon(":/aitum/media/tiktok.png");
	QIcon platformIconTwitter = QIcon(":/aitum/media/twitter.png");
	QIcon platformIconTrovo = QIcon(":/aitum/media/trovo.png");
	QIcon platformIconFacebook = QIcon(":/aitum/media/facebook.png");
	QIcon platformIconUnknown = QIcon(":/aitum/media/unknown.png");

	static void frontend_event(enum obs_frontend_event event, void *private_data);

	static void stream_output_stop(void *data, calldata_t *calldata);
	static void stream_output_start(void *data, calldata_t *calldata);

private slots:
	void NewerVersionAvailable(QString version);

public:
	MultistreamDock(QWidget *parent = nullptr);
	~MultistreamDock();
	void LoadVerticalOutputs(bool firstLoad = true);
};
