#pragma once

#include "config-dialog.hpp"
#include <obs.h>
#include <obs-frontend-api.h>
#include <QFrame>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>
#include <QString>

// Forward declare the obs_websocket_vendor type
typedef void* obs_websocket_vendor;

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
	QLabel *mainPlatformIconLabel = nullptr;
	QString mainPlatformUrl;

	QString newer_version_available;

	QTimer videoCheckTimer;
	video_t *mainVideo = nullptr;
	std::vector<video_t *> oldVideo;

	std::vector<std::tuple<std::string, obs_output_t *, QPushButton *>> outputs;
	obs_data_array_t *vertical_outputs = nullptr;
	bool exiting = false;

	void LoadSettingsFile();
	void LoadSettings();
	void LoadOutput(obs_data_t *data, bool vertical);
	void SaveSettings();

	bool StartOutput(obs_data_t *settings, QPushButton *streamButton);

	void outputButtonStyle(QPushButton *button);

	void storeMainStreamEncoders();

	QIcon streamActiveIcon = QIcon(":/aitum/media/streaming.svg");
	QIcon streamInactiveIcon = QIcon(":/aitum/media/stream.svg");

	static void frontend_event(enum obs_frontend_event event, void *private_data);

	static void stream_output_stop(void *data, calldata_t *calldata);
	static void stream_output_start(void *data, calldata_t *calldata);

private slots:
	void NewerVersionAvailable(QString version);

public:
	// Correct declaration of websocket_vendor
	obs_websocket_vendor websocket_vendor = nullptr;

	void register_websocket_procedures();

	MultistreamDock(QWidget *parent = nullptr);
	~MultistreamDock();
	void LoadVerticalOutputs(bool firstLoad = true);
	bool update_stream_settings_by_index(int index, const QString &new_stream_key, const QString &new_stream_server);
	bool start_stream_by_index(int index); // Start a stream based on index
	bool stop_stream_by_index(int index);  // Stop a stream based on index

    static void update_stream_settings_websocket(obs_data_t *request, obs_data_t *response, void *priv_data);
	static void start_stream_websocket(obs_data_t *request, obs_data_t *response, void *priv_data); // Start stream
    static void stop_stream_websocket(obs_data_t *request, obs_data_t *response, void *priv_data);  // Stop stream
};
