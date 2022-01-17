#include "TargetTester.h"


TargetTester::TargetTester(QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);
	ui.btn_load_file->setCornerRadius(3);
	ui.btn_save_file->setCornerRadius(3);
	ui.btn_start->setCornerRadius(3);
	ui.btn_pause->setCornerRadius(3);
	ui.btn_end->setCornerRadius(3);
	connect(ui.btn_add, &QtMaterialFlatButton::clicked, this, &TargetTester::AddTarget2Table);
	connect(ui.btn_remove, &QtMaterialFlatButton::clicked, this, &TargetTester::RemoveTableTarget);
	connect(ui.btn_clear, &QtMaterialFlatButton::clicked, this, &TargetTester::ClearTable);
	initializeTable();
}

TargetTester::~TargetTester() {

}

void TargetTester::ChangeTheme(const QColor& color) {
	ui.btn_load_file->setBackgroundColor(color);
	ui.btn_save_file->setBackgroundColor(color);
	ui.btn_start->setBackgroundColor(color);
	ui.btn_pause->setBackgroundColor(color);
	ui.btn_end->setBackgroundColor(color);
	ui.btn_add->setBackgroundColor(color);
	ui.btn_remove->setBackgroundColor(color);
	ui.btn_clear->setBackgroundColor(color);

	ui.CB_indicate->setCheckedColor(color);
	ui.CB_random_pose->setCheckedColor(color);

	ui.LE_tar_id->setInkColor(color);
	ui.LE_tar_start_A->setInkColor(color);
	ui.LE_tar_end_A->setInkColor(color);
	ui.LE_tar_start_E->setInkColor(color);
	ui.LE_tar_end_E->setInkColor(color);
	ui.LE_tar_start_R->setInkColor(color);
	ui.LE_tar_end_R->setInkColor(color);
	ui.LE_tar_V->setInkColor(color);
	ui.LE_tar_RCS->setInkColor(color);


	for (int i = 0; i < ui.TW_tar->rowCount(); ++i) {
		QWidget* indicate_widget = ui.TW_tar->cellWidget(i, 10);
		if(indicate_widget !=nullptr){
			QtMaterialCheckBox* cb_indicate = qobject_cast<QtMaterialCheckBox*>(indicate_widget->children().at(1));
			if (cb_indicate != nullptr) {
				cb_indicate->setCheckedColor(Qt::white);
			}
		}
		QWidget* pose_widget = ui.TW_tar->cellWidget(i, 11);
		if (pose_widget != nullptr) {
			QtMaterialCheckBox* cb_pose = qobject_cast<QtMaterialCheckBox*>(pose_widget->children().at(1));
			if (cb_pose != nullptr) {
				cb_pose->setCheckedColor(Qt::white);
			}
		}
	}

	ui.TW_tar->setStyleSheet(QString("QTableWidget::item:selected{background-color:rgb(%1,%2,%3);}")
		.arg(color.red()).arg(color.green()).arg(color.blue())
	);
	////��ȡ���淽ʽ��ȡ
	//if (QWidget* w = ui->tableWidget_IdentifiedPrimitives->cellWidget(row, column))//�Ȼ�ȡwidget
	//{
	//	QCheckBox* checkBox = qobject_cast<QCheckBox*>(w->children().at(1));  //ͨ��children������checkbox
	//	if (checkBox)
	//	{
	//		if (checkBox->checkState() == Qt::Unchecked) //δѡ��
	//		{
	//			//����
	//		}
	//	}
	//}
	//ui.TW_tar->setItem(ui.TW_tar->rowCount() - 1, 10, item);
	//item = new QTableWidgetItem;
	//item->setCheckState(Qt::Checked);
	//ui.TW_tar->setItem(ui.TW_tar->rowCount() - 1, 11, item);
}

void TargetTester::ChangeFont(const QFont& font, int font_size, bool is_bold, int lang_type) {
	QFont new_font = font;
	new_font.setPixelSize(font_size);
	new_font.setBold(is_bold);
	if (lang_type == UI_LANG_ZH_CN_TYPE) {
		ui.btn_load_file->setFont(new_font);
		ui.btn_save_file->setFont(new_font);
		ui.btn_start->setFont(new_font);
		ui.btn_pause->setFont(new_font);
		ui.btn_end->setFont(new_font);
		
		ui.LB_target_type->setFont(new_font);
		ui.LB_A_start->setFont(new_font);
		ui.LB_A_end->setFont(new_font);
		ui.LB_E_start->setFont(new_font);
		ui.LB_E_end->setFont(new_font);
		ui.LB_R_start->setFont(new_font);
		ui.LB_R_end->setFont(new_font);
		ui.LB_V->setFont(new_font);
		
		ui.CB_indicate->setFont(new_font);
		ui.CB_random_pose->setFont(new_font);
		ui.btn_add->setFont(new_font);
		ui.btn_remove->setFont(new_font);
		ui.btn_clear->setFont(new_font);
		ui.CB_tar_type->setFont(new_font);
	}
	if (lang_type == UI_LANG_EN_US_TYPE) {
		ui.TW_tar->setFont(new_font);
		ui.LB_id->setFont(new_font);
		ui.LB_RCS->setFont(new_font);
		ui.LE_tar_id->setFont(new_font);
		ui.LE_tar_start_A->setFont(new_font);
		ui.LE_tar_end_A->setFont(new_font);
		ui.LE_tar_start_E->setFont(new_font);
		ui.LE_tar_end_E->setFont(new_font);
		ui.LE_tar_start_R->setFont(new_font);
		ui.LE_tar_end_R->setFont(new_font);
		ui.LE_tar_V->setFont(new_font);
		ui.LE_tar_RCS->setFont(new_font);
	}
}

void TargetTester::AddTarget2Table() {
	
	UI::WaitingSendTarget target;
	target.target_id = ui.LE_tar_id->text().toULongLong();
	target.target_type = ui.CB_tar_type->currentIndex();
	target.start_A = ui.LE_tar_start_A->text().toDouble();
	target.end_A = ui.LE_tar_end_A->text().toDouble();
	target.start_E = ui.LE_tar_start_E->text().toDouble();
	target.end_E = ui.LE_tar_end_E->text().toDouble();
	target.start_R = ui.LE_tar_start_R->text().toDouble();
	target.end_R = ui.LE_tar_end_R->text().toDouble();
	target.V = ui.LE_tar_V->text().toDouble();
	target.RCS = ui.LE_tar_RCS->text().toDouble();
	target.is_indicate = ui.CB_indicate->isChecked();
	target.is_random_pose = ui.CB_random_pose->isChecked();
	Add2Table(target);

	ui.LE_tar_id->setText(QString::number(ui.LE_tar_id->text().toInt() + 1));
}

void TargetTester::RemoveTableTarget() {
	/*��ȡѡ�е��б����������Ŀ*/
	QList<QTableWidgetItem*> list = ui.TW_tar->selectedItems();
	if (list.count() <= 0){
		return;
	}

	/*���б��������Ƴ���Ŀ*/
	QList<QTableWidgetItem*>::iterator itr;
	for (itr = list.begin(); itr != list.end(); ++itr) {
		if (*itr == nullptr) {
			continue;
		}
		/*��ȡ��Ŀ���к�*/
		int row = ui.TW_tar->row(*itr);
		if (row != -1) {
			ui.TW_tar->removeRow(row);
		}
	}

}

void TargetTester::ClearTable() {

	for (int row = ui.TW_tar->rowCount()-1; row >=0; --row)	{
		ui.TW_tar->removeRow(row);
	}
}

void TargetTester::initializeTable() {
	ui.TW_tar->setColumnCount(12);
	QStringList headers;
	headers << "ID" << ZH_CN("����") << ZH_CN("��ʼ��λ") << ZH_CN("������λ")
		<< ZH_CN("��ʼ����") << ZH_CN("��������") << ZH_CN("��ʼб��") << ZH_CN("����б��")
		<< ZH_CN("�ٶ�") << ZH_CN("RCS") << ZH_CN("Ŀ��ָʾ") << ZH_CN("�����̬");
	ui.TW_tar->setHorizontalHeaderLabels(headers);

	ui.TW_tar->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.TW_tar->verticalHeader()->setHidden(true);
	ui.TW_tar->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void TargetTester::Add2Table(const UI::WaitingSendTarget& target) {
	ui.TW_tar->setRowCount(ui.TW_tar->rowCount() + 1);
	ui.TW_tar->setItem(ui.TW_tar->rowCount()-1,0, new QTableWidgetItem(QString::number(target.target_id)));


	{// Ŀ��ָʾ
		QWidget* wg_indicate = new QWidget(ui.TW_tar);
		QHBoxLayout* hLayout = new QHBoxLayout();

		QtMaterialCheckBox* cb_indicate = new QtMaterialCheckBox(this);
		cb_indicate->setCheckedColor(ui.btn_add->backgroundColor());
		cb_indicate->setChecked(target.is_indicate);
		hLayout->addWidget(cb_indicate);
		hLayout->setMargin(0);
		hLayout->setAlignment(cb_indicate, Qt::AlignCenter);
		wg_indicate->setLayout(hLayout);
		ui.TW_tar->setCellWidget(ui.TW_tar->rowCount() - 1, 10, wg_indicate);
	}
	
	{// �����̬
		QtMaterialCheckBox* cb_random_pose = new QtMaterialCheckBox(this);
		cb_random_pose->setCheckedColor(ui.btn_add->backgroundColor());
		cb_random_pose->setChecked(target.is_random_pose);
		QWidget* wg_random_pose = new QWidget(ui.TW_tar);

		QHBoxLayout* hLayout = new QHBoxLayout();
		hLayout->addWidget(cb_random_pose);
		hLayout->setMargin(0);
		hLayout->setAlignment(cb_random_pose, Qt::AlignCenter);
		wg_random_pose->setLayout(hLayout);
		ui.TW_tar->setCellWidget(ui.TW_tar->rowCount() - 1, 11, wg_random_pose);
	}
	

	


	////��ȡ���淽ʽ��ȡ
	//if (QWidget* w = ui->tableWidget_IdentifiedPrimitives->cellWidget(row, column))//�Ȼ�ȡwidget
	//{
	//	QCheckBox* checkBox = qobject_cast<QCheckBox*>(w->children().at(1));  //ͨ��children������checkbox
	//	if (checkBox)
	//	{
	//		if (checkBox->checkState() == Qt::Unchecked) //δѡ��
	//		{
	//			//����
	//		}
	//	}
	//}
	//ui.TW_tar->setItem(ui.TW_tar->rowCount() - 1, 10, item);
	//item = new QTableWidgetItem;
	//item->setCheckState(Qt::Checked);
	//ui.TW_tar->setItem(ui.TW_tar->rowCount() - 1, 11, item);
}
