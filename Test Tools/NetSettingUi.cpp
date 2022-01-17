#include "NetSettingUi.h"

NetSettingUi::NetSettingUi(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.TG_use_target ,&QtMaterialToggle::toggled ,this ,&NetSettingUi::ChangeTargetNetEnable);
	connect(ui.TG_use_structs ,&QtMaterialToggle::toggled ,this ,&NetSettingUi::ChangeStructsNetEnable);
	connect(ui.btn_save ,&QtMaterialFlatButton::clicked ,this ,&NetSettingUi::SaveNetConfig);
	connect(ui.btn_cancel ,&QtMaterialFlatButton::clicked ,this ,&NetSettingUi::RecoverNetConfig);

	QRegExp regx("[0-9]{3}");
	QValidator* validator_ip = new QRegExpValidator(regx ,this);
	regx = QRegExp("[0-9]{5}");
	QValidator* validator_port = new QRegExpValidator(regx ,this);

	ui.LE_ip_all_1->setValidator(validator_ip);
	ui.LE_ip_all_2->setValidator(validator_ip);
	ui.LE_ip_all_3->setValidator(validator_ip);
	ui.LE_ip_all_4->setValidator(validator_ip);
	ui.LE_port_all->setValidator(validator_port);

	ui.LE_ip_target_1->setValidator(validator_ip);
	ui.LE_ip_target_2->setValidator(validator_ip);
	ui.LE_ip_target_3->setValidator(validator_ip);
	ui.LE_ip_target_4->setValidator(validator_ip);
	ui.LE_port_target->setValidator(validator_port);

	ui.LE_ip_structs_1->setValidator(validator_ip);
	ui.LE_ip_structs_2->setValidator(validator_ip);
	ui.LE_ip_structs_3->setValidator(validator_ip);
	ui.LE_ip_structs_4->setValidator(validator_ip);
	ui.LE_port_structs->setValidator(validator_port);

	RecoverNetConfig();
	ui.btn_save->setEnabled(false);

}

NetSettingUi::~NetSettingUi(){

}

void NetSettingUi::ChangeTargetNetEnable(bool enable) {
	ui.WG_target_ip_port->setEnabled(enable);
}

void NetSettingUi::ChangeStructsNetEnable(bool enable) {
	ui.WG_structs_ip_port->setEnabled(enable);
}

void NetSettingUi::SaveNetConfig() {
	ConfigCore::instance()->SetValue(
		GetIpStr(ui.LE_ip_all_1->text() ,ui.LE_ip_all_2->text() ,ui.LE_ip_all_3->text(),ui.LE_ip_all_4->text()).toStdString()
		,"ui" ,"net" ,"all" ,"ip" ,nullptr);
	ConfigCore::instance()->SetValue(
		GetIpStr(ui.LE_ip_target_1->text(),ui.LE_ip_target_2->text() ,ui.LE_ip_target_3->text(),ui.LE_ip_target_4->text()).toStdString()
		,"ui" ,"net" ,"target" ,"ip" ,nullptr);
	ConfigCore::instance()->SetValue(
		GetIpStr(ui.LE_ip_structs_1->text() ,ui.LE_ip_structs_2->text() ,ui.LE_ip_structs_3->text(),ui.LE_ip_structs_4->text()).toStdString()
		,"ui" ,"net" ,"structs" ,"ip" ,nullptr);

	ConfigCore::instance()->SetValue(ui.LE_port_all->text().toInt() ,"ui" ,"net" ,"all" ,"port" ,nullptr);
	ConfigCore::instance()->SetValue(ui.LE_port_target->text().toInt() ,"ui" ,"net" ,"target" ,"port" ,nullptr);
	ConfigCore::instance()->SetValue(ui.LE_port_structs->text().toInt(),"ui" ,"net" ,"structs" ,"port" ,nullptr);

	ConfigCore::instance()->SetValue(ui.TG_use_target->isChecked() ,"ui" ,"net" ,"target" ,"use_net" ,nullptr);
	ConfigCore::instance()->SetValue(ui.TG_use_structs->isChecked() ,"ui" ,"net" ,"structs" ,"use_net" ,nullptr);
}

void NetSettingUi::RecoverNetConfig() {
	std::string ip_all_str = ConfigCore::instance()->ReadValue("ui" ,"net" ,"all" ,"ip" ,nullptr);
	std::string ip_target_str = ConfigCore::instance()->ReadValue("ui" ,"net" ,"target" ,"ip" ,nullptr);
	std::string ip_structs_str = ConfigCore::instance()->ReadValue("ui" ,"net" ,"structs" ,"ip" ,nullptr);

	int port_all = boost::lexical_cast<int>(ConfigCore::instance()->ReadValue("ui" ,"net" ,"all" ,"port" ,nullptr));
	int port_target = boost::lexical_cast<int>(ConfigCore::instance()->ReadValue("ui" ,"net" ,"target" ,"port" ,nullptr));
	int port_structs = boost::lexical_cast<int>(ConfigCore::instance()->ReadValue("ui" ,"net" ,"structs" ,"port" ,nullptr));

	bool use_target_net = ConfigCore::instance()->ReadValue("ui" ,"net" ,"target" ,"use_net" ,nullptr)=="true";
	bool use_structs_net = ConfigCore::instance()->ReadValue("ui" ,"net" ,"structs" ,"use_net" ,nullptr)=="true";

	SetAllNet(ip_all_str ,port_all);
	SetTargetNet(ip_target_str ,port_target ,use_target_net);
	SetStructsNet(ip_structs_str ,port_structs ,use_structs_net);
}

void NetSettingUi::on_LE_ip_all_1_textChanged(const QString& text) {
	ui.btn_save->setEnabled(true);
	ui.btn_cancel->setEnabled(true);
	if (text.toInt()>255) {
		ui.LE_ip_all_1->setText("255");
	}
	if (!ui.TG_use_target->isChecked()) {
		ui.LE_ip_target_1->setText(text);
	}
	if (!ui.TG_use_structs->isChecked()) {
		ui.LE_ip_structs_1->setText(text);
	}
}

void NetSettingUi::on_LE_ip_all_2_textChanged(const QString& text) {
	ui.btn_save->setEnabled(true);
	ui.btn_cancel->setEnabled(true);
	if (text.toInt()>255) {
		ui.LE_ip_all_2->setText("255");
	}
	if (!ui.TG_use_target->isChecked()) {
		ui.LE_ip_target_2->setText(text);
	}
	if (!ui.TG_use_structs->isChecked()) {
		ui.LE_ip_structs_2->setText(text);
	}
}

void NetSettingUi::on_LE_ip_all_3_textChanged(const QString& text) {
	ui.btn_save->setEnabled(true);
	ui.btn_cancel->setEnabled(true);
	if (text.toInt()>255) {
		ui.LE_ip_all_3->setText("255");
	}
	if (!ui.TG_use_target->isChecked()) {
		ui.LE_ip_target_3->setText(text);
	}
	if (!ui.TG_use_structs->isChecked()) {
		ui.LE_ip_structs_3->setText(text);
	}
}

void NetSettingUi::on_LE_ip_all_4_textChanged(const QString& text) {
	ui.btn_save->setEnabled(true);
	ui.btn_cancel->setEnabled(true);
	if (text.toInt()>255) {
		ui.LE_ip_all_4->setText("255");
	}
	if (!ui.TG_use_target->isChecked()) {
		ui.LE_ip_target_4->setText(text);
	}
	if (!ui.TG_use_structs->isChecked()) {
		ui.LE_ip_structs_4->setText(text);
	}
}

void NetSettingUi::on_LE_port_all_textChanged(const QString& text) {
	if (!ui.TG_use_target->isChecked()) {
		ui.LE_port_target->setText(text);
	}
	if (!ui.TG_use_structs->isChecked()) {
		ui.LE_port_structs->setText(text);
	}
}

void NetSettingUi::ChangeTheme(const QColor& color) {
	ui.btn_save->setBackgroundColor(color);
	ui.btn_cancel->setBackgroundColor(color);
	ui.TG_use_structs->setActiveColor(color);
	ui.TG_use_target->setActiveColor(color);

	ui.LE_ip_all_1->setInkColor(color);
	ui.LE_ip_all_2->setInkColor(color);
	ui.LE_ip_all_3->setInkColor(color);
	ui.LE_ip_all_4->setInkColor(color);
	ui.LE_port_all->setInkColor(color);

	ui.LE_ip_target_1->setInkColor(color);
	ui.LE_ip_target_2->setInkColor(color);
	ui.LE_ip_target_3->setInkColor(color);
	ui.LE_ip_target_4->setInkColor(color);
	ui.LE_port_target->setInkColor(color);

	ui.LE_ip_structs_1->setInkColor(color);
	ui.LE_ip_structs_2->setInkColor(color);
	ui.LE_ip_structs_3->setInkColor(color);
	ui.LE_ip_structs_4->setInkColor(color);
	ui.LE_port_structs->setInkColor(color);
}

void NetSettingUi::ChangeFont(const QFont& font, int font_size, bool is_bold, int lang_type) {
	QFont new_font = font;
	new_font.setPixelSize(font_size);
	new_font.setBold(is_bold);
	if (lang_type == UI_LANG_ZH_CN_TYPE) {
		font.family();
		ui.GB_all->setFont(new_font);
		ui.LB_port_all->setFont(new_font);
		ui.LB_target_use->setFont(new_font);
		ui.LB_port_target->setFont(new_font);
		ui.GB_target->setFont(new_font);
		ui.GB_structs->setFont(new_font);
		ui.LB_structs_use->setFont(new_font);
		ui.LB_port_structs->setFont(new_font);
		ui.btn_save->setFont(new_font);
		ui.btn_cancel->setFont(new_font);
	}
	if (lang_type == UI_LANG_EN_US_TYPE) {
		ui.LB_ip_all->setFont(new_font);
		ui.LB_ip_targte->setFont(new_font);
		ui.LB_ip_structs->setFont(new_font);

		ui.LE_ip_all_1->setFont(new_font);
		ui.LE_ip_all_2->setFont(new_font);
		ui.LE_ip_all_3->setFont(new_font);
		ui.LE_ip_all_4->setFont(new_font);
		ui.LE_port_all->setFont(new_font);

		ui.LE_ip_target_1->setFont(new_font);
		ui.LE_ip_target_2->setFont(new_font);
		ui.LE_ip_target_3->setFont(new_font);
		ui.LE_ip_target_4->setFont(new_font);
		ui.LE_port_target->setFont(new_font);

		ui.LE_ip_structs_1->setFont(new_font);
		ui.LE_ip_structs_2->setFont(new_font);
		ui.LE_ip_structs_3->setFont(new_font);
		ui.LE_ip_structs_4->setFont(new_font);
		ui.LE_port_structs->setFont(new_font);
	}
}

QString NetSettingUi::GetIpStr(const QString& ip_1_str ,const QString& ip_2_str ,const QString& ip_3_str ,const QString& ip_4_str) {
	if (ip_1_str.isEmpty()||ip_2_str.isEmpty()||ip_3_str.isEmpty()||ip_4_str.isEmpty()) {
		return "";
	}
	return ip_1_str+'.'+ip_2_str+'.'+ip_3_str+'.'+ip_4_str;
}

QString NetSettingUi::GetIpStr(const QString& ip_str ,int position) {
	QStringList ip_str_list = ip_str.split('.');
	if (ip_str_list.size()<position) {
		return "";
	}
	return ip_str_list[position-1];
}

void NetSettingUi::SetAllNet(const std::string& ip_str ,int port_num) {
	ui.LE_ip_all_1->setText(GetIpStr(QString::fromStdString(ip_str) ,1));
	ui.LE_ip_all_2->setText(GetIpStr(QString::fromStdString(ip_str) ,2));
	ui.LE_ip_all_3->setText(GetIpStr(QString::fromStdString(ip_str) ,3));
	ui.LE_ip_all_4->setText(GetIpStr(QString::fromStdString(ip_str) ,4));
	ui.LE_port_all->setText(QString::number(port_num));
}

void NetSettingUi::SetTargetNet(const std::string& ip_str ,int port_num ,bool use) {
	ui.LE_ip_target_1->setText(GetIpStr(QString::fromStdString(ip_str) ,1));
	ui.LE_ip_target_2->setText(GetIpStr(QString::fromStdString(ip_str) ,2));
	ui.LE_ip_target_3->setText(GetIpStr(QString::fromStdString(ip_str) ,3));
	ui.LE_ip_target_4->setText(GetIpStr(QString::fromStdString(ip_str) ,4));
	ui.LE_port_target->setText(QString::number(port_num));
	ui.TG_use_target->setChecked(use);
	ui.WG_target_ip_port->setEnabled(use);
}

void NetSettingUi::SetStructsNet(const std::string& ip_str ,int port_num ,bool use) {
	ui.LE_ip_structs_1->setText(GetIpStr(QString::fromStdString(ip_str) ,1));
	ui.LE_ip_structs_2->setText(GetIpStr(QString::fromStdString(ip_str) ,2));
	ui.LE_ip_structs_3->setText(GetIpStr(QString::fromStdString(ip_str) ,3));
	ui.LE_ip_structs_4->setText(GetIpStr(QString::fromStdString(ip_str) ,4));
	ui.LE_port_structs->setText(QString::number(port_num));
	ui.TG_use_structs->setChecked(use);
	ui.WG_structs_ip_port->setEnabled(use);
}
