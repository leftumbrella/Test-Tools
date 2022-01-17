#pragma once

#include <QWidget>
#include <QValidator>
#include "FirstIncludeUi.h"
#include "ConfigCore.h"
#include "ui_NetSettingUi.h"
#include <boost/lexical_cast.hpp>

class NetSettingUi : public QWidget
{
	Q_OBJECT

public:
	NetSettingUi(QWidget *parent = Q_NULLPTR);
	~NetSettingUi();
private slots:
	void ChangeTargetNetEnable(bool enable);
	void ChangeStructsNetEnable(bool enable);
	void SaveNetConfig();
	void RecoverNetConfig();
	void on_LE_ip_all_1_textChanged(const QString& text);
	void on_LE_ip_all_2_textChanged(const QString& text);
	void on_LE_ip_all_3_textChanged(const QString& text);
	void on_LE_ip_all_4_textChanged(const QString& text);
	void on_LE_port_all_textChanged(const QString& text);
public slots:
	void ChangeTheme(const QColor& color);
	void ChangeFont(const QFont& font, int font_size, bool is_bold, int lang_type);
private:
	inline QString GetIpStr(const QString& ip_1_str ,const QString& ip_2_str ,const QString& ip_3_str,const QString& ip_4_str);
	inline QString GetIpStr(const QString& ip_str ,int position);
	inline void SetAllNet(const std::string& ip_str ,int port_num);
	inline void SetTargetNet(const std::string& ip_str ,int port_num ,bool use);
	inline void SetStructsNet(const std::string& ip_str ,int port_num ,bool use);
private:
	Ui::NetSettingUi ui;
};
