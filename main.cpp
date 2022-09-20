#include <gtk/gtk.h>
#include "./nodes.cpp"

using namespace std;

/*static void*/
/*click1_cb (GtkButton *btn, gpointer user_data) {*/
	/*const gchar *s;*/

	/*s = gtk_button_get_label (btn);*/
	/*if (g_strcmp0 (s, "Hello.") == 0)*/
		/*gtk_button_set_label (btn, "Good-bye.");*/
	/*else*/
		/*gtk_button_set_label (btn, "Hello.");*/
/*}*/

struct Checkbox_clicked_data{
	Logic* log;
	string hechoname;
};

static void
toggle_checkbox (GtkCheckButton *cbtn, gpointer user_data) {
	//GtkWindow *win = GTK_WINDOW (user_data);
	//gtk_window_destroy (win);
	Checkbox_clicked_data* cdd = (Checkbox_clicked_data*) user_data;
	//Logic* log = (Logic*) user_data;


	
	update_hecho(&(((Logic*)cdd->log)->hm),
			(string)cdd->hechoname,
			gtk_check_button_get_active(cbtn)
			);

	printHechoMap(&(((Logic*)cdd->log)->hm));

	cout << gtk_check_button_get_active(cbtn) << endl;
}

struct Args_app_activate{
	map<string, GtkCheckButton*>* checkBtnLst;
	GtkWidget* resCont;
	GtkWidget* descCont;
	vector<GtkWidget*>* resLst;
	Logic* mlog;
};

struct Args_click_result_link{
	//Logic* log;
	Args_app_activate* aaa;
	string hechoname;
};

static gboolean
click_result_link (GtkWidget* btnlink, gpointer user_data){
	GtkTextBuffer* tb;
	string desc;

	Args_click_result_link* arg = (Args_click_result_link*) user_data;
	desc = info_get_desc(arg->hechoname);
	cout << "bbbbb " << arg->hechoname << endl;

	// set text to buffer
	tb = gtk_text_view_get_buffer (GTK_TEXT_VIEW (arg->aaa->descCont));
	gtk_text_buffer_set_text (tb, desc.c_str(), -1);

	return TRUE;
}

//struct Args_update_checkbox{

//};

/*static void
update_checkbox_list (
		map<string, GtkCheckButton*>* cbl,
		map<string, bool>* hm,
		vector<string>* inputh){

	for (int i = 0; i < inputh->size(); i++){
		gtk_check_button_set_active((*cbl)[(*inputh)[i]], (*hm)[(*inputh)[i]]);
	}
}*/

static void
reset_description (Args_app_activate* aaa){
	GtkTextBuffer* tb;

	// empty buffer
	tb = gtk_text_view_get_buffer (GTK_TEXT_VIEW (aaa->descCont));
	gtk_text_buffer_set_text (tb, "", -1);

}


static void
update_results (Args_app_activate* aaa){
	
	vector<GtkWidget*>* resLst = (vector<GtkWidget*>*) aaa->resLst;
	Logic* log = (Logic*) aaa->mlog;
	GtkWidget* resCont = (GtkWidget*) aaa->resCont;

	// delete all
	for(int i = 0; i < resLst->size(); i++){
		gtk_box_remove(GTK_BOX(resCont), (*resLst)[i]);
		//gtk_box_append (GTK_BOX(ibox), chebox);
	}

	resLst->clear();
	
	// create all
	for(int i = 0; i < log->outputh.size(); i++){
		string name = log->outputh[i]; 

		if (log->hm[name]){
			string label = "[" + name + "] " + info_get_title(name);
			Args_click_result_link* arglink = new Args_click_result_link();
			arglink->aaa = aaa;
			arglink->hechoname = name;


			cout << name << endl;

			// create link button
			//gtk_link_button_new_with_label().
			GtkWidget *btn;
			GtkWidget *btnlbl;

			btn = gtk_link_button_new_with_label("", label.c_str());
			btnlbl = gtk_widget_get_first_child(btn);
			gtk_label_set_wrap(GTK_LABEL(btnlbl), true);
			gtk_label_set_justify(GTK_LABEL(btnlbl), GTK_JUSTIFY_LEFT);
			gtk_label_set_xalign(GTK_LABEL(btnlbl), 0);

			g_signal_connect (btn, "activate-link", G_CALLBACK (click_result_link), arglink);

			// add to parent
			gtk_box_append (GTK_BOX(resCont), btn);
			// add to list
			resLst->push_back (btn);
			//checkBtnLst->insert(make_pair(log->inputh[i], GTK_CHECK_BUTTON(chebox)));
		}
	}

}

static void
click_step (GtkButton* btn, gpointer user_data){

	Args_app_activate* aaa = (Args_app_activate*) user_data;

	//vector<GtkWidget*>* resLst = (vector<GtkWidget*>*) aaa->resLst;
	Logic* log = (Logic*) aaa->mlog;

	steps(&log->hm, &log->rl);
	printHechoMap(&log->hm);

	update_results(aaa);
}


static void
click_reset (GtkButton* btn, gpointer user_data){
	// args
	Args_app_activate* aaa = (Args_app_activate*) user_data;
	map<string, GtkCheckButton*>* checkBtnLst = (map<string, GtkCheckButton*>*) aaa->checkBtnLst;
	Logic* log = (Logic*) aaa->mlog;

	// reset 
	reset_noinputs(&log->hm, &log->inputh);

	// update checkbox list
	// update_checkbox_list(checkBtnLst, &log->hm, &log->inputh);

	//steps(&log->hm, &log->rl);
	printHechoMap(&log->hm);
	update_results(aaa);
	reset_description(aaa);
}


static void
app_activate (GApplication *app, gpointer user_data) {
	/*GtkWidget *win;*/
	/*GtkWidget *box;*/
	/*GtkWidget *btn1;*/
	/*GtkWidget *btn2;*/

	/*win = gtk_application_window_new (GTK_APPLICATION (app));*/
	/*gtk_window_set_title (GTK_WINDOW (win), "lb4");*/
	/*gtk_window_set_default_size (GTK_WINDOW (win), 400, 300);*/

	/*box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);*/
	/*[>gtk_box_set_homogeneous (GTK_BOX (box), TRUE);<]*/
	/*gtk_window_set_child (GTK_WINDOW (win), box);*/

	/*btn1 = gtk_button_new_with_label ("Hello.");*/
	/*g_signal_connect (btn1, "clicked", G_CALLBACK (click1_cb), NULL);*/

	/*btn2 = gtk_button_new_with_label ("Quit");*/
	/*g_signal_connect (btn2, "clicked", G_CALLBACK (click2_cb), win);*/

	/*gtk_box_append (GTK_BOX (box), btn1);*/
	/*gtk_box_append (GTK_BOX (box), btn2);*/

	/*gtk_widget_show (win);*/

	Args_app_activate* aaa = (Args_app_activate*) user_data;
	map<string, GtkCheckButton*>* checkBtnLst = (map<string, GtkCheckButton*>*) aaa->checkBtnLst;
	//vector<GtkWidget*>* resLst = (map<string, GtkCheckButton*>*) aaa->checkBtnLst;
	Logic* log = (Logic*) aaa->mlog;

	printHechoMap(&log->hm);

	GtkBuilder *build;
	GtkWidget *win;

	// input
	GtkWidget *ibox;

	// buttons
	GtkWidget *btnReset;
	GtkWidget *btnStep;


	build = gtk_builder_new_from_file ("../main.ui");
	win = GTK_WIDGET (gtk_builder_get_object (build, "win"));
	gtk_window_set_application (GTK_WINDOW (win), GTK_APPLICATION (app));

	ibox = GTK_WIDGET (gtk_builder_get_object (build, "box_input"));

	// create input checkbox
	for (int i = 0; i < log->inputh.size(); i++){
		string label;
		label = log->inputh[i] + ". " + info_get_title(log->inputh[i]);
		Checkbox_clicked_data* ccd = new Checkbox_clicked_data();
		ccd->log = log;
		ccd->hechoname = log->inputh[i];

		GtkWidget *chebox;
		chebox = gtk_check_button_new_with_label(label.c_str());
		gtk_check_button_set_active(GTK_CHECK_BUTTON (chebox), log->hm[log->inputh[i]]);

		g_signal_connect (chebox, "toggled", G_CALLBACK (toggle_checkbox), ccd);

		// add to parent
		gtk_box_append (GTK_BOX(ibox), chebox);
		// add to list
		checkBtnLst->insert(make_pair(log->inputh[i], GTK_CHECK_BUTTON(chebox)));

	}

	// result
	GtkWidget *resCont;
	resCont = GTK_WIDGET (gtk_builder_get_object (build, "box_results"));
	aaa->resCont = resCont;

	// description
	GtkWidget *descCont;
	descCont = GTK_WIDGET (gtk_builder_get_object (build, "box_description"));
	aaa->descCont = descCont;

	// buttons
	btnReset = GTK_WIDGET (gtk_builder_get_object (build, "btn_reset"));
	g_signal_connect (btnReset, "clicked", G_CALLBACK (click_reset), user_data);

	btnStep = GTK_WIDGET (gtk_builder_get_object (build, "btn_step"));
	g_signal_connect (btnStep, "clicked", G_CALLBACK (click_step), user_data);

	gtk_widget_show(win);
	/*nb = GTK_WIDGET (gtk_builder_get_object (build, "nb"));*/
}

int
main (int argc, char **argv) {
	GtkApplication *app;
	int stat;
	
	// checkbox list
	map<string, GtkCheckButton*> checkBtnLst;
	// results list
	vector<GtkWidget*> resLst;

	Logic mlog;
	logic_setup(
		&(mlog.hm),
		&(mlog.rl),
		&(mlog.rlPending),
		&(mlog.rlDone),
		&(mlog.inputh),
		&(mlog.outputh)
		);

	printHechoMap(&mlog.hm);

	// args
	Args_app_activate* aaa = new Args_app_activate();
	aaa->checkBtnLst = &checkBtnLst;
	aaa->resLst = &resLst;
	aaa->mlog = &mlog;

	// start app
	app = gtk_application_new ("com.github.woynert", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (app_activate), aaa);
	//g_signal_connect (app, "activate", G_CALLBACK (app_activate), &mlog);
	stat =g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);
	return stat;
}
