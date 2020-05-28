#ifndef __scorer_hpp__
#define __scorer_hpp__

#include <scorer.h>


template < typename Os >
void scorer :: print_class_stats (Os & os)
{

	os << std :: left << std :: setw(40) << "Classes";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << classes[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "TP(True positive/hit)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << TP[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "FN(False negative/miss/type 2 error)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << FN[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "FP(False positive/type 1 error/false alarm)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << FP[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "TN(True negative/correct rejection)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << TN[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "POP(Population)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << POP[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "P(Condition positive or support)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << P[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "N(Condition negative)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << N[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "TOP(Test outcome positive)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << TOP[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "TON(Test outcome negative)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << TON[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "TPR(Sensitivity / recall / hit rate / true positive rate)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << TPR[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "TNR(Specificity or true negative rate)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << TNR[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "PPV(Precision or positive predictive value)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << PPV[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "NPV(Negative predictive value)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << NPV[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "FNR(Miss rate or false negative rate)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << FNR[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "FPR(Fall-out or false positive rate)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << FPR[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "FDR(False discovery rate)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << FDR[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "FOR(False omission rate)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << FOR[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "ACC(Accuracy)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << ACC[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "F1(F1 score - harmonic mean of precision and sensitivity)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << F1_SCORE[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "F0.5(F0.5 score)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << F05_SCORE[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "F2(F2 score)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << F2_SCORE[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "MCC(Matthews correlation coefficient)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << MCC[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "BM(Informedness or bookmaker informedness)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << BM[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "MK(Markedness)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << MK[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "ICSI(Individual classification success index)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << ICSI[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "PLR(Positive likelihood ratio)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << PLR[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "NLR(Negative likelihood ratio)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << NLR[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "DOR(Diagnostic odds ratio)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << DOR[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "PRE(Prevalence)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << PRE[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "G(G-measure geometric mean of precision and sensitivity)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << G[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "RACC(Random accuracy)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << RACC[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "ERR(Error rate)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << ERR_ACC[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "RACCU(Random accuracy unbiased)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << RACCU[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "J(Jaccard index)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << jaccard_index[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "IS(Information score)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << IS[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "CEN(Confusion entropy)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << CEN[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "MCEN(Modified confusion entropy)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << MCEN[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "AUC(Area Under the ROC curve)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << AUC[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "dInd(Distance index)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << dIND[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "sInd(Similarity index)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << sIND[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "DP(Discriminant power)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << DP[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "Y(Youden index)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << Y[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "PLRI(Positive likelihood ratio interpretation)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << PLRI[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "NLRI(Negative likelihood ratio interpretation)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << NLRI[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "DPI(Discriminant power interpretation)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << DPI[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "AUCI(AUC value interpretation)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << AUCI[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "GI(Gini index)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << GI[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "LS(Lift score)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << LS[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "AM(Difference between automatic and manual classification)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << AM[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "OP(Optimized precision)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << OP[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "IBA(Index of balanced accuracy)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << IBA[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "GM(G-mean geometric mean of specificity and sensitivity)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << GM[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "Q(Yule Q - coefficient of colligation)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << Q[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "AGM(Adjusted geometric mean)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << AGM[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "MCCI(Matthews correlation coefficient interpretation)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << MCCI[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "AGF(Adjusted F-score)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << AGF[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "OC(Overlap coefficient)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << OC[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "OOC(Otsuka-Ochiai coefficient)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << OOC[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "AUPR(Area under the PR curve)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << AUPR[i] << " ";
	os << std :: endl;

	os << std :: left << std :: setw(40) << "BCD(Bray-Curtis dissimilarity)";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << BCD[i] << " ";
	os << std :: endl;

}



template < typename Os >
void scorer :: print_overall_stats (Os & os)
{

	os << std :: left << std :: setw(40) << "Overall ACC" << std :: setw(20) << overall_accuracy << std :: endl;

	os << std :: left << std :: setw(40) << "Overall RACCU" << std :: setw(20) << overall_random_accuracy_unbiased << std :: endl;

	os << std :: left << std :: setw(40) << "Overall RACC" << std :: setw(20) << overall_random_accuracy << std :: endl;

	os << std :: left << std :: setw(40) << "Kappa" << std :: setw(20) << overall_kappa << std :: endl;

	os << std :: left << std :: setw(40) << "PC_PI" << std :: setw(20) << PC_PI << std :: endl;

	os << std :: left << std :: setw(40) << "PC_AC1" << std :: setw(20) << PC_AC1 << std :: endl;

	os << std :: left << std :: setw(40) << "PC_S" << std :: setw(20) << PC_S << std :: endl;

	os << std :: left << std :: setw(40) << "Scott PI" << std :: setw(20) << PI << std :: endl;

	os << std :: left << std :: setw(40) << "Get AC1" << std :: setw(20) << AC1 << std :: endl;

	os << std :: left << std :: setw(40) << "Bennett S" << std :: setw(20) << S << std :: endl;

	os << std :: left << std :: setw(40) << "Kappa Standard Error" << std :: setw(20) << kappa_SE << std :: endl;

	os << std :: left << std :: setw(40) << "Kappa Unbiased" << std :: setw(20) << kappa_unbiased << std :: endl;

	os << std :: left << std :: setw(40) << "Kappa No Prevalence" << std :: setw(20) << kappa_no_prevalence << std :: endl;

	os << std :: left << std :: setw(40) << "Kappa 95% CI up" << std :: setw(20) << kappa_CI_up << std :: endl;

	os << std :: left << std :: setw(40) << "Kappa 95% CI down" << std :: setw(20) << kappa_CI_down << std :: endl;

	os << std :: left << std :: setw(40) << "Standard Error" << std :: setw(20) << overall_accuracy_se << std :: endl;

	os << std :: left << std :: setw(40) << "95% CI up" << std :: setw(20) << overall_accuracy_ci_up << std :: endl;

	os << std :: left << std :: setw(40) << "95% CI down" << std :: setw(20) << overall_accuracy_ci_down << std :: endl;

	os << std :: left << std :: setw(40) << "Chi-Squared" << std :: setw(20) << chi_square << std :: endl;

	os << std :: left << std :: setw(40) << "Phi-Squared" << std :: setw(20) << phi_square << std :: endl;

	os << std :: left << std :: setw(40) << "Cramer V" << std :: setw(20) << cramer_V << std :: endl;

	os << std :: left << std :: setw(40) << "Response Entropy" << std :: setw(20) << response_entropy << std :: endl;

	os << std :: left << std :: setw(40) << "Reference Entropy" << std :: setw(20) << reference_entropy << std :: endl;

	os << std :: left << std :: setw(40) << "Cross Entropy" << std :: setw(20) << cross_entropy << std :: endl;

	os << std :: left << std :: setw(40) << "Joint Entropy" << std :: setw(20) << join_entropy << std :: endl;

	os << std :: left << std :: setw(40) << "Conditional Entropy" << std :: setw(20) << conditional_entropy << std :: endl;

	os << std :: left << std :: setw(40) << "Mutual Information" << std :: setw(20) << mutual_information << std :: endl;

	os << std :: left << std :: setw(40) << "KL Divergence" << std :: setw(20) << kl_divergence << std :: endl;

	os << std :: left << std :: setw(40) << "Lambda B" << std :: setw(20) << lambda_B << std :: endl;

	os << std :: left << std :: setw(40) << "Lambda A" << std :: setw(20) << lambda_A << std :: endl;

	os << std :: left << std :: setw(40) << "Chi-Squared DF" << std :: setw(20) << DF << std :: endl;

	os << std :: left << std :: setw(40) << "Overall J" << std :: setw(20) << overall_jaccard_index << std :: endl;

	os << std :: left << std :: setw(40) << "Hamming loss" << std :: setw(20) << hamming_loss << std :: endl;

	os << std :: left << std :: setw(40) << "Zero-one Loss" << std :: setw(20) << zero_one_loss << std :: endl;

	os << std :: left << std :: setw(40) << "NIR" << std :: setw(20) << NIR << std :: endl;

	os << std :: left << std :: setw(40) << "P-value" << std :: setw(20) << p_value << std :: endl;

	os << std :: left << std :: setw(40) << "Overall CEN" << std :: setw(20) << overall_CEN << std :: endl;

	os << std :: left << std :: setw(40) << "Overall MCEN" << std :: setw(20) << overall_MCEN << std :: endl;

	os << std :: left << std :: setw(40) << "Overall MCC" << std :: setw(20) << overall_MCC << std :: endl;

	os << std :: left << std :: setw(40) << "RR" << std :: setw(20) << RR << std :: endl;

	os << std :: left << std :: setw(40) << "CBA" << std :: setw(20) << CBA << std :: endl;

	os << std :: left << std :: setw(40) << "AUNU" << std :: setw(20) << AUNU << std :: endl;

	os << std :: left << std :: setw(40) << "AUNP" << std :: setw(20) << AUNP << std :: endl;

	os << std :: left << std :: setw(40) << "RCI" << std :: setw(20) << RCI << std :: endl;

	os << std :: left << std :: setw(40) << "CSI" << std :: setw(20) << CSI << std :: endl;

	os << std :: left << std :: setw(40) << "Pearson C" << std :: setw(20) << overall_pearson_C << std :: endl;

	os << std :: left << std :: setw(40) << "TPR Micro, PPV Micro, F1 Micro" << std :: setw(20) << TPR_PPV_F1_micro << std :: endl;

	os << std :: left << std :: setw(40) << "SOA6(Matthews)" << std :: setw(20) << MCC_analysis << std :: endl;

	os << std :: left << std :: setw(40) << "SOA4(Cicchetti)" << std :: setw(20) << kappa_analysis_cicchetti << std :: endl;

	os << std :: left << std :: setw(40) << "SOA1(Landis & Koch)" << std :: setw(20) << kappa_analysis_koch << std :: endl;

	os << std :: left << std :: setw(40) << "SOA2(Fleiss)" << std :: setw(20) << kappa_analysis_fleiss << std :: endl;

	os << std :: left << std :: setw(40) << "SOA3(Altman)" << std :: setw(20) << kappa_analysis_altman << std :: endl;

	os << std :: left << std :: setw(40) << "SOA5(Cramer)" << std :: setw(20) << V_analysis << std :: endl;

	os << std :: left << std :: setw(40) << "TPR Macro" << std :: setw(20) << TPR_macro << std :: endl;

	os << std :: left << std :: setw(40) << "PPV Macro" << std :: setw(20) << PPV_macro << std :: endl;

	os << std :: left << std :: setw(40) << "ACC Macro" << std :: setw(20) << ACC_macro << std :: endl;

	os << std :: left << std :: setw(40) << "F1 Macro" << std :: setw(20) << F1_macro << std :: endl;

}



void scorer :: print ()
{
	this->print_class_stats < std :: ostream >(std :: cout);
	std :: cout << std :: endl;
	this->print_overall_stats < std :: ostream >(std :: cout);
}

void scorer :: dump (const std :: string & filename)
{
	std :: ofstream os (filename + ".cl_stats");
	os << "stats," << std :: endl;
	this->print_class_stats < std :: ofstream >(os);
	os.close();

	os.open(filename + ".overall_stats");
	os << "stats,score" << std :: endl;
	this->print_overall_stats < std :: ofstream >(os);
	os.close();
}

template < typename dtype >
int * scorer :: encoder (dtype * arr, const int & size)
{

	int * encode = new int [size];

	std :: unordered_set < dtype > lbl (arr, arr + size, size * sizeof(dtype));

	std :: transform (arr, arr + size, encode, [&](const dtype & l) {return std :: distance(lbl.begin(), lbl.find(l));});

	return encode;
}


#endif // __scorer_hpp__

