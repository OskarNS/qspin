#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {

    ui->setupUi(this);
    this->setWindowTitle("QSpin");

    //Setting font of groupbox titles
    // The stylesheet is not inherited to children of the QGroupBox, thereby the labels won't suffer the effect of the change in the parents stylesheet.
    //QGroupBox *statespaceprop = this->findChild<QGroupBox *>("groupBox_4");
    //statespaceprop->setStyleSheet("QGroupBox { font-weight: bold; text-decoration: underline; } ");
    //QGroupBox *statespacespecs = this->findChild<QGroupBox *>("groupBox_5");
    //statespacespecs->setStyleSheet("QGroupBox { font-weight: bold; text-decoration: underline; } ");
    //QGroupBox *memoryusage = this->findChild<QGroupBox *>("groupBox_6");
    //memoryusage->setStyleSheet("QGroupBox { font-weight: bold; text-decoration: underline; } ");

    // Connecting to objects

    //Statespaceprop groupbox
    spinVerLabel = this->findChild<QLabel *>("spinVerLabel");
    evalLabel = this->findChild<QLabel *>("evalLabel");
    partialLabel = this->findChild<QLabel *>("partialLabel_2");
    neverLabel = this->findChild<QLabel *>("neverLabel_2");
    assertionLabel = this->findChild<QLabel *>("assertionLabel_2");
    acceptanceLabel = this->findChild<QLabel *>("acceptanceLabel_2");
    CycleTypeLabel = this->findChild<QLabel * >("LabelCycleType");
    invalidLabel = this->findChild<QLabel *>("invalidLabel_2");

    // Statespacespec groupbox
    errorLabel = this->findChild<QLabel *>("errorLabel");
    depthLabel = this->findChild<QLabel *>("depthLabel");
    storedstatesLabel = this->findChild<QLabel *>("storedstatesLabel");
    matchedstatesLabel = this->findChild<QLabel *>("matchedstatesLabel");
    transitionLabel = this->findChild<QLabel *>("transitionLabel");
    atomicLabel = this->findChild<QLabel *>("atomicLabel");
    statesizeLabel = this->findChild<QLabel *>("statesizeLabel");
    hashconflictsLabel = this->findChild<QLabel *>("hashconflictsLabel");
    hashsizeLabel = this->findChild<QLabel *>("hashsizeLabel");

    // Memory usage groupbox
    statememoryLabel = this->findChild<QLabel *>("statememoryLabel");
    hashmemoryLabel = this->findChild<QLabel *>("hashmemoryLabel");
    DFSmemoryLabel = this->findChild<QLabel *>("DFSmemoryLabel");
    totalmemoryLabel = this->findChild<QLabel *>("totalmemoryLabel");

    timestampLabel = this->findChild<QLabel *>("timestampLabel");
    ltlList = this->findChild<QListWidget *>("ltlList");

    // ## Toolbar ##
    QAction *actionLoad = this->findChild<QAction *>("actionLoad");
    QAction *actionSave = this->findChild<QAction *>("actionSave");
    QAction *actionAbort = this->findChild<QAction *>("actionAbort");
    actionCheckSyntax = this->findChild<QAction *>("actionCheck_syntax");
    QAction *actionLoad_Ltl = this->findChild<QAction *>("actionLoad_Ltl");

    connect(actionLoad, SIGNAL(triggered()) , this,SLOT(loadFile()));
    connect(actionSave, SIGNAL(triggered()) , this,SLOT(saveFile()));
    connect(actionAbort, SIGNAL(triggered()),this,SLOT(terminateProcess()));
    connect(actionCheckSyntax, SIGNAL(triggered()), this , SLOT(runCheckSyntax()));
    connect(actionLoad_Ltl, SIGNAL(triggered()), this, SLOT(loadLtlFile()));

    // ## Verify tab ##
    buttonVerify = this->findChild<QPushButton *>("buttonVerify");
    // properties
    radioSafety = this->findChild<QRadioButton *>("radioSafety");
    radioAcceptance = this->findChild<QRadioButton *>("radioAcceptance");
    radioLiveness = this->findChild<QRadioButton *>("radioLiveness");
    checkFair = this->findChild<QCheckBox *>("checkFairness");
    connect(buttonVerify, SIGNAL(clicked()) , this, SLOT(runVerify()));
    newltlButton = this->findChild<QPushButton *>("newltlButton");
    deleteltlButton = this->findChild<QPushButton*>("deleteltlButton");

    connect(newltlButton,SIGNAL(clicked()),this,SLOT(newLtl()));
    connect(deleteltlButton,SIGNAL(clicked()),this,SLOT(deleteLtl()));
    // connect(ltlList,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(runVerify()));


    // ## Simulation tab
    buttonRandomSim = this->findChild<QPushButton *>("buttonRandomSim");
    buttonBackSim = this->findChild<QPushButton*>("buttonSimBackward");
    buttonForwardSim = this->findChild<QPushButton*>("buttonSimForward");
    radioInteractive = this->findChild<QRadioButton*>("radioInteractiveSim");
    radioGuided = this->findChild<QRadioButton*>("radioGuidedSim");
    spinBoxSteps = this->findChild<QSpinBox *>("spinBoxSteps");
    simulationTypeLabel = this->findChild<QLabel*>("labelSimType");
    fileLabel = this->findChild<QLabel*>("labelSimFile");
    connect(buttonRandomSim, SIGNAL(clicked()), this, SLOT(runSimulation()));
    connect(buttonForwardSim, SIGNAL(clicked()),this,SLOT(simulationStepForward()));
    connect(buttonBackSim,SIGNAL(clicked()),this,SLOT(simulationStepBackwards()));
    //connect(variableTabel,SIGNAL(cellChanged(int,int),this,SLOT()));
    processTable = this->findChild<QTableWidget*>("tableProceses");
    variableTable = this->findChild<QTableWidget*>("tableVariabels");
    simulationSteps = this->findChild<QListWidget*>("listSteps");

    // Interactive Tab
    buttonInteractiveSim = this->findChild<QPushButton *>("buttonInteractiveSim");
    listChoises = this->findChild<QListWidget *>("choisesList");
    connect(buttonInteractiveSim, SIGNAL(clicked()), this, SLOT(runInteractive()));
    processTable_I = this->findChild<QTableWidget*>("tableProceses_I");
    variableTable_I = this->findChild<QTableWidget*>("tableVariabels_I");
    simulationSteps_I = this->findChild<QListWidget*>("listSteps_I");
    fileLabel_I = this->findChild<QLabel*>("labelSimFile_I");

    // options
    radioColapse = this->findChild<QRadioButton *>("radioDCOLLAPSE");
    radioDH4 = this->findChild<QRadioButton *>("radioDH4");
    checkHSize = this->findChild<QCheckBox *>("checkHashSize");
    spinBoxHSize = this->findChild<QSpinBox *>("spinBoxHashSize");
    spinBoxSDepth = this->findChild<QSpinBox *>("spinBoxSearchDepth");
    checkOptDepth = this->findChild<QCheckBox *>("checkOptimizeDepth");

    // ## other ##
    status = this->findChild<QStatusBar *>("statusbar");
    outputLog = this->findChild<QTextEdit *>("log");
    editor = (CodeEditor*) this->findChild<QPlainTextEdit *>("editor");

    new Highlighter(editor->document());
    iconFallback();
}

MainWindow::~MainWindow() {
    fileCleanup();
    delete ui;
}

void MainWindow::loadFile() {
    if (filename!=NULL) fileCleanup();
    QString tempPath = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Promela Files (*.pml);;All files (*)"));
    if (tempPath!=NULL) {
        editor->clear();
        QFile file(tempPath);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        status->showMessage("Failed to open "+tempPath);
        } else {
            QTextStream in(&file);
            while(!in.atEnd()) {
                editor->appendPlainText(in.readLine());
            }
            file.close();
            path = tempPath;
            QRegExp rx("/((([a-z]|[A-Z]|\\d)+).pml)");
            rx.indexIn(path);
            filename = rx.cap(1);
            status->showMessage("File loaded: "+path);
        }
    } else {
        status->showMessage("No file chosen");
    }
}

void MainWindow::loadLtlFile(){
    LTLpath = QFileDialog::getOpenFileName(this, tr("Open LTL File"),"",tr("LTL Files (*.ltl);;All Files (*)"));
    if (LTLpath!=NULL) {
        QFile LTLfile(LTLpath);

        QRegExp rx("/((([a-z]|[A-Z]|\\d)+).ltl)");
        rx.indexIn(LTLpath);
        filename = rx.cap(1);

        if (!LTLfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        status->showMessage("Failed to open "+LTLpath);
        } else {
            QTextStream in(&LTLfile);
            while(!in.atEnd()) {
                //std::cout << in.readLine().toStdString() << std::endl;
                //ltlList->addItem(in.readLine());
                QString currentLine = in.readLine();
                bool breakout = false;
                for (int i = 0; i < ltlList->count(); i++){
                    if(ltlList->item(i)->text() == currentLine )
                         breakout = true;
                }

                //item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
                //item->setCheckState(Qt::Unchecked); // AND initialize check state
                if(!breakout){
                    QListWidgetItem* item = new QListWidgetItem(currentLine, ltlList);
                    item->setFlags(item->flags() | Qt::ItemIsEditable);
                }
            }
            LTLfile.close();
            status->showMessage("LTL file loaded: "+LTLpath);
        }
    } else {
        status->showMessage("No file chosen");
    }
}

void MainWindow::saveLtlFile(){
    if (LTLpath == NULL){
        if (path != NULL){
            int lastPoint = path.lastIndexOf(".");
            QString pathNameNoExt = path.left(lastPoint);
            LTLpath = pathNameNoExt + ".ltl";
        }else { path = QFileDialog::getSaveFileName(this, tr("Save File"),"",tr("LTL Files (*.ltl);;All Files (*)")); }

    }
    QFile file(LTLpath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        status->showMessage("Could not save "+LTLpath);
    } else {
        QTextStream out(&file);
        for (int i = 0; i < ltlList->count(); i++){
            out << ltlList->item(i)->text()+ "\n" ;
        }

        file.close();
        status->showMessage("File saved: "+LTLpath);
    }

}

void MainWindow::saveFile() {
    //TODO: Implement functionality to save all LTL's in ltl file
    if (path==NULL) {
        path = QFileDialog::getSaveFileName(this, tr("Save File"),"",tr("Promela Files (*.pml);;All Files (*)"));
    }
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        status->showMessage("Could not save "+path);
    } else {
        QTextStream out(&file);
        out << editor->toPlainText();
        file.close();
        status->showMessage("File saved: "+path);
    }
}

void MainWindow::runVerify(){
    fileCleanup();
    if (prepareRun()) {
        compileOpts.clear();
        // COMPILE OPTIONS
        if (radioColapse->isChecked())           compileOpts << "-DCOLLAPSE ";
        else if (radioDH4->isChecked())          compileOpts << "-DH4 ";
        if (radioSafety->isChecked())            compileOpts <<"-DSAFETY ";
        else if (radioLiveness->isChecked())     compileOpts <<"-DNP ";
        compileOpts << "-o" << "pan";
        // TYPE
        verType = VerificationRun::Safety;
        if (radioAcceptance->isChecked())
            verType = VerificationRun::Acceptance;
        if (radioLiveness->isChecked())
            verType = VerificationRun::Liveness;
        // FETCH LTL
        ltl = "";
        if(verType == VerificationRun::Acceptance && ltlList->count() > 0){
           ltl = getLtl();
        }
        // setup SyntaxRun
        syntaxRun = new SyntaxRun(path,ltl);
        thread = connectProcess(syntaxRun);
        connect(syntaxRun, SIGNAL(noErrors()),this,SLOT(verify()));
        connect(syntaxRun, SIGNAL(hasErrors()),this,SLOT(displayErrors()));
        thread->start();
    }
}

void MainWindow::verify(){
        clearVerificationTab();
        verificationRun = new VerificationRun(path, verType,checkFair->isChecked(),ltl, compileOpts,spinBoxSDepth->value(),hashSize());
        outputLog->clear();
        thread = connectProcess(verificationRun);
        connect(this,SIGNAL(closeProcess()),verificationRun,SLOT(terminateProcess())); // Signal for terminating the process running Spin
        connect(verificationRun,SIGNAL(finished(SpinRun*)),this,SLOT(updateVerificationTab()));
        thread->start();
}

void MainWindow::runInteractive() {
    if (prepareRun()) {

        fileLabel->setText(filename);

        syntaxRun = new SyntaxRun(path,"");
        thread = connectProcess(syntaxRun);
        connect(syntaxRun, SIGNAL(noErrors()),this,SLOT(interactive()));
        connect(syntaxRun, SIGNAL(hasErrors()),this,SLOT(displayErrors()));
        thread->start();
    }
}

void MainWindow::runSimulation() {
    if (prepareRun()) {

        simType = SimulationRun::Random;
        if (radioGuided->isChecked()) {
            simType = SimulationRun::Guided;
            simulationTypeLabel->setText("Guided");
        } else simulationTypeLabel->setText("Random");
        fileLabel->setText(filename);
        syntaxRun = new SyntaxRun(path,"");
        thread = connectProcess(syntaxRun);
        connect(syntaxRun, SIGNAL(noErrors()),this,SLOT(simulation()));
        connect(syntaxRun, SIGNAL(hasErrors()),this,SLOT(displayErrors()));
        thread->start();
    }
}

void MainWindow::simulation(){
    simulationRun = new SimulationRun(path,simType,spinBoxSteps->value());
    thread = connectProcess(simulationRun);
    connect(this,SIGNAL(closeProcess()),simulationRun,SLOT(terminateProcess())); // Signal for terminating the process running Spin
    //connect(simulationRun,SIGNAL(readReady(SpinRun*)),this,SLOT(createSimulationTab()));
    connect(simulationRun,SIGNAL(finished(SpinRun*)),this,SLOT(createSimulationTab()));
    //connect(simulationRun,SIGNAL(readReady(SpinRun*)),this,SLOT(processReadReady(SpinRun*)));
    connect(simulationSteps,SIGNAL(itemSelectionChanged()),this,SLOT(simulationStepClicked()));
    buttonForwardSim->setDisabled(false);
    thread->start();
}

void MainWindow::interactive(){
    interactiveRun = new SimulationRun(path,SimulationRun::Interactive,spinBoxSteps->value());
    thread = connectProcess(interactiveRun);
    connect(this,SIGNAL(closeProcess()),interactiveRun,SLOT(terminateProcess())); // Signal for terminating the process running Spin
    connect(interactiveRun,SIGNAL(readReady(SpinRun*)),this,SLOT(createInteractiveTab()));
    connect(interactiveRun,SIGNAL(finished(SpinRun*)),this,SLOT(createInteractiveTab()));
    connect(interactiveRun,SIGNAL(readReady(SpinRun*)),this,SLOT(processReadReady(SpinRun*)));
    connect(listChoises,SIGNAL(activated(QModelIndex)),interactiveRun,SLOT(commitChoise(QModelIndex)));
    connect(simulationSteps_I,SIGNAL(itemSelectionChanged()),this,SLOT(interactiveStepClicked()));
    buttonForwardSim->setDisabled(false);
    thread->start();
}

QThread* MainWindow::connectProcess(SpinRun* run){
    outputLog->clear();
    thread = new QThread(this);
    run->moveToThread(thread);
    connect(thread,SIGNAL(started()),run,SLOT(start()));
    connect(run, SIGNAL(finished(SpinRun*)),this,SLOT(processFinished(SpinRun*)));
    connect(run, SIGNAL(finished(SpinRun*)), thread, SLOT(quit()));
    connect(run, SIGNAL(statusChanged(SpinRun*)),this,SLOT(processStatusChange(SpinRun*)));
    connect(thread, SIGNAL(finished()),thread,SLOT(deleteLater()));
    connect(thread,SIGNAL(started()),this,SLOT(disableRunButtons()));
    //connect(thread,SIGNAL(),run, SLOT(deleteLater())); // INDSAT FOR AT FÅ PROCESSEN TIL AT LUKKE
    connect(run,SIGNAL(finished(SpinRun*)),this,SLOT(enableRunButtons()));

    return thread;
}

void MainWindow::runCheckSyntax() {
    if(prepareRun()){
        syntaxRun = new SyntaxRun(path,"");
        thread = connectProcess(syntaxRun);
        connect(syntaxRun, SIGNAL(hasErrors()),this,SLOT(displayErrors()));
        thread->start();
    }
}

void MainWindow::displayErrors() {
    QStringList lineNoList = syntaxRun->lineNoList;
    QStringList errorList = syntaxRun->errorList;

    for(int i = 0 ; i < lineNoList.count();i++){
        outputLog->append("Error at line "+lineNoList[i]+": "+errorList[i]);
        if (lineNoList[i].toInt() > editor->blockCount()){
            if (ltlList->item(selectedLtl)){
                ltlList->item(selectedLtl)->setBackgroundColor(Qt::red);
            }
            lineNoList.removeAt(i);
        }
    }
    if (lineNoList.count() > 0){
        editor->HighlightErrorLines(lineNoList);

    }
}

int MainWindow::hashSize() {
    if (checkHSize->isChecked())
        return spinBoxHSize->value();
    else return -1;
}

QString MainWindow::getLtl(){
    for (int i = 0; i < ltlList->count(); i++){
        if(ltlList->item(i)->isSelected()){
            selectedLtl = i;
            return ltlList->item(i)->text();
        }
    }
    selectedLtl = -1;
    return "";
}

void MainWindow::disableRunButtons(){
    buttonVerify->setDisabled(true);
    buttonRandomSim->setDisabled(true);
    buttonInteractiveSim->setDisabled(true);
    actionCheckSyntax->setDisabled(true);
}

void MainWindow::enableRunButtons(){
    buttonVerify->setEnabled(true);
    buttonRandomSim->setEnabled(true);
    buttonInteractiveSim->setEnabled(true);
    actionCheckSyntax->setEnabled(true);
}

void MainWindow::simulationStepForward() {
        simulationRun->goForward();
        updateSimulationTab(simulationRun,variableTable,processTable,simulationSteps);
}

void MainWindow::simulationStepBackwards() {
        simulationRun->goBackwards();
        updateSimulationTab(interactiveRun,variableTable_I,processTable_I,simulationSteps_I);
}

void MainWindow::processFinished(SpinRun* run) {
    outputLog->append(run->readOutput());
    status->showMessage("Finished");
}

void MainWindow::processReadReady(SpinRun* run) {
    outputLog->append(run->readOutput());
}

void MainWindow::processStatusChange(SpinRun* run) {
    status->showMessage(run->readStatus());
}

// returns true if there is a file to run
bool MainWindow::prepareRun(bool clearLog){
    if (path!=NULL) saveFile();
    else if (path== NULL && editor->blockCount() > 2){ saveFile();}
    else loadFile();
    if (ltlList->count() > 0) saveLtlFile();
    if (clearLog) outputLog->clear();
    return path!=NULL;
}

void MainWindow::terminateProcess(){
    emit closeProcess();
    listChoises->clear();
    outputLog->clear();
    status->showMessage("Process killed.");
    enableRunButtons();
    //}
}

// TODO: Flytte den her så spinRun kan bruge den til at fjerne filer?
void MainWindow::fileCleanup(){
    QDir dir(QDir::currentPath());
    dir.setNameFilters(QStringList() << "pan*" << "*.trail");
    dir.setFilter(QDir::Files);
    dir.remove(path+".trail");
    foreach(QString dirFile, dir.entryList())
    {
        dir.remove(dirFile);
    }
}

void MainWindow::newLtl(){
    QListWidgetItem *item = new QListWidgetItem("ltl newName {}" ,ltlList);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
}

void MainWindow::deleteLtl(){
    for (int i = 0; i < ltlList->count(); i++){
        if(ltlList->item(i)->isSelected()){
            ltlList->takeItem(i);
        }
    }
}

void MainWindow::updateSimulationTab(SimulationRun *run, QTableWidget *variableTable, QTableWidget *processTable, QListWidget *stepList) {
    QList<SimulationRun::variable> variables = run->getVariables();
    QList<SimulationRun::proc> procs = run->getProcs();
    // Variablse tab
    for (int i = 0 ; i < variables.length() ; i++) {
        variableTable->setItem(variables[i].id,0,new QTableWidgetItem(variables[i].name));
        variableTable->setItem(variables[i].id,1,new QTableWidgetItem(variables[i].value));
    }
    // Process tab
    for (int i = 0 ; i < procs.length() ; i++) {
        int procLine = procs[i].line;
        processTable->setItem(procs[i].id,0,new QTableWidgetItem(procs[i].name));
        if (procLine<0) {
            processTable->setItem(procs[i].id,1,new QTableWidgetItem("-"));
        } else {
            processTable->setItem(procs[i].id,1,new QTableWidgetItem(QString::number(procLine)));
        }
    }
    editor->HighlightProcesses(run->getProcs());
    stepList->item(run->getCurrentIndex())->setSelected(true);
}

void MainWindow::createSimulationTab() {
    populateSimulationLists(simulationRun,variableTable,processTable,simulationSteps);
}

void MainWindow::createInteractiveTab() {
    populateSimulationLists(interactiveRun,variableTable_I,processTable_I,simulationSteps_I);
    // Interactive Choises
    listChoises->clear();
    QList<SimulationRun::choise> choises = interactiveRun->getChoises();
    foreach (SimulationRun::choise choise , choises) {
        listChoises->addItem(new QListWidgetItem(choise._proc.name+" | "+choise.operation));
    }
    processTable->resizeColumnsToContents();
    variableTable->resizeColumnsToContents();
}

void MainWindow::simulationStepClicked(){
    updateStepList(simulationSteps, simulationRun);
    updateSimulationTab(simulationRun,variableTable,processTable,simulationSteps);
    buttonForwardSim->setEnabled(simulationRun->canGoForward());
    buttonBackSim->setEnabled(simulationRun->canGoBackwards());
}

void MainWindow::interactiveStepClicked(){
    updateStepList(simulationSteps_I, interactiveRun);
    updateSimulationTab(interactiveRun,variableTable_I,processTable_I,simulationSteps_I);
}

void MainWindow::populateSimulationLists(SimulationRun* run, QTableWidget* variableTable, QTableWidget* processTable, QListWidget *stepList){
    QList<SimulationRun::variable> variables = run->getVariables();
    QList<SimulationRun::proc> procs = run->getProcs();
    QStringList operations = run->getOperations();
    variableTable->setRowCount(variables.length());
    processTable->setRowCount(procs.length());
    stepList->clear();
    // Variablse tab
    for (int i = 0 ; i < variables.length() ; i++) {
        variableTable->setItem(variables[i].id,0,new QTableWidgetItem(variables[i].name));
        variableTable->setItem(variables[i].id,1,new QTableWidgetItem(variables[i].value));
    }
    // Process tab
    for (int i = 0 ; i < procs.length() ; i++) {
        processTable->setItem(procs[i].id,0,new QTableWidgetItem(procs[i].name));
        processTable->setItem(procs[i].id,1,new QTableWidgetItem("-"));
    }
    // Steps list
    foreach (QString operation , operations) {
        stepList->addItem(new QListWidgetItem(operation));
    }
    if (int index = run->getCurrentIndex()) {
        stepList->item(index)->setSelected(true);
    }
    processTable->resizeColumnsToContents();
    variableTable->resizeColumnsToContents();
}

void MainWindow::updateStepList(QListWidget *stepList , SimulationRun *run) {
    if (run && stepList->selectedItems().length()>0) {
        int newIndex = stepList->selectionModel()->selectedIndexes()[0].row();
        int oldIndex = run->getCurrentIndex();
        if (newIndex<oldIndex) {
            run->goBackwards(oldIndex-newIndex);
        } else if (newIndex>oldIndex) {
            run->goForward(newIndex-oldIndex);
        }
    }
}

void MainWindow::listChoiseActivated(QModelIndex index) {
    if (simulationRun) {
        QList<SimulationRun::choise> choises = simulationRun->getChoises();
        SimulationRun::choise choise = choises[index.row()];
    }
}

void MainWindow::updateVerificationTab(){
    // SPINVERSIONLABEL
    spinVerLabel->setText(verificationRun->spinVer);
    // EVALUATIONLABEL
    evalLabel->setStyleSheet("background-color: " + verificationRun->eval+ ";");
    // STATESPACE PROP
    // PARTIAL ORDER REDUCTION LABEL
    partialLabel->setText(verificationRun->partial);
    // NEVER CLAIM LABEL
    neverLabel->setText(verificationRun->never);
    // ASSERTION LABEL
    assertionLabel->setText(verificationRun->assertion);
    //ACCEPTANCE LABEL
    CycleTypeLabel->setText(verificationRun->acceptanceType.append(" cyles:"));
    acceptanceLabel->setText(verificationRun->acceptance);
    //INVALID END STATES LABEL
    invalidLabel->setText(verificationRun->invalid);
    // STATESPACE SPECS
    errorLabel->setText(verificationRun->errors);
    depthLabel->setText(verificationRun->depth);
    storedstatesLabel->setText(verificationRun->storedStates);
    matchedstatesLabel->setText(verificationRun->matchedStates);
    transitionLabel->setText(verificationRun->transitions);
    atomicLabel->setText(verificationRun->atomic);
    statesizeLabel->setText(verificationRun->statesize);
    hashconflictsLabel->setText(verificationRun->hashconflict);
    hashsizeLabel->setText(verificationRun->hashsize);
    // MEMORY USAGE
    statememoryLabel->setText(verificationRun->statememory);
    hashmemoryLabel->setText(verificationRun->hashmemory);
    DFSmemoryLabel->setText(verificationRun->DFSmemory);
    totalmemoryLabel->setText(verificationRun->totalmemory);

    timestampLabel->setText(verificationRun->timestamp);

    //IF LTL RUN, update ltl evaluation:
    if(verificationRun->verificationType==VerificationRun::Acceptance && ltlList->count() > 0 && selectedLtl != -1){
        if(verificationRun->errors == "0"){
           ltlList->item(selectedLtl)->setBackgroundColor(Qt::green);
        }
        else{
            ltlList->item(selectedLtl)->setBackgroundColor(Qt::red);
        }
    }

    // Update search depth value
    if (checkOptDepth->isChecked()) {
        spinBoxSDepth->setValue((verificationRun->depth).toInt()+10);
    }
}

void MainWindow::clearVerificationTab() {
    // Verification tab
    spinVerLabel->clear();
    evalLabel->clear();
    partialLabel->clear();
    neverLabel->clear();
    assertionLabel->clear();
    acceptanceLabel->clear();
    invalidLabel->clear();
    simulationTypeLabel->clear();
    fileLabel->clear();
    errorLabel->clear();
    depthLabel->clear();
    storedstatesLabel->clear();
    matchedstatesLabel->clear();
    transitionLabel->clear();
    atomicLabel->clear();
    statesizeLabel->clear();
    hashconflictsLabel->clear();
    hashsizeLabel->clear();
    statememoryLabel->clear();
    hashmemoryLabel->clear();
    DFSmemoryLabel->clear();
    totalmemoryLabel->clear();
    timestampLabel->clear();
}

void MainWindow::iconFallback() {
    if (QString::compare("linux",OS)) { // will set icons if system is NOT linux
        QIcon loadFile;
        QIcon saveFile;
        QIcon abort;
        QIcon forward;
        QIcon backward;

        loadFile.addFile(":icons/document-open",QSize(24, 24));
        saveFile.addFile(":icons/document-save",QSize(24, 24));
        abort.addFile(":icons/process-stop",QSize(24, 24));
        forward.addFile(":icons/go-next",QSize(24, 24));
        backward.addFile(":icons/go-previous",QSize(24, 24));

        ui->actionLoad->setIcon(loadFile);
        ui->actionSave->setIcon(saveFile);
        ui->actionAbort->setIcon(abort);
        ui->buttonSimForward->setIcon(forward);
        ui->buttonSimBackward->setIcon(backward);
    }
}
