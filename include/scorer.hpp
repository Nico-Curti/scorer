#ifndef __scorer_hpp__
#define __scorer_hpp__

#include <scorer.h>

template < typename Os >
void scorer :: print_class_stats (Os & os)
{
	os << std :: left << std :: setw(40) << "classes";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << classes[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "TP";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << TP[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "FN";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << FN[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "FP";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << FP[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "TN";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << TN[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "POP";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << POP[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "P";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << P[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "N";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << N[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "TOP";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << TOP[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "TON";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << TON[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "TPR";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << TPR[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "TNR";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << TNR[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "PPV";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << PPV[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "NPV";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << NPV[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "FNR";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << FNR[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "FPR";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << FPR[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "FDR";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << FDR[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "FOR";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << FOR[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "ACC";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << ACC[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "F1_SCORE";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << F1_SCORE[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "F05_SCORE";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << F05_SCORE[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "F2_SCORE";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << F2_SCORE[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "MCC";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << MCC[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "BM";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << BM[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "MK";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << MK[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "PLR";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << PLR[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "NLR";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << NLR[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "DOR";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << DOR[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "PRE";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << PRE[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "G";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << G[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "RACC";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << RACC[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "ERR_ACC";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << ERR_ACC[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "RACCU";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << RACCU[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "jaccard_index";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << jaccard_index[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "IS";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << IS[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "CEN";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << CEN[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "MCEN";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << MCEN[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "AUC";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << AUC[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "dIND";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << dIND[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "sIND";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << sIND[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "DP";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << DP[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "Y";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << Y[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "PLRI";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << PLRI[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "NLRI";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << NLRI[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "DPI";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << DPI[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "AUCI";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << AUCI[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "GI";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << GI[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "LS";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << LS[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "AM";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << AM[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "OP";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << OP[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "IBA";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << IBA[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "GM";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << GM[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "Q";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << Q[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "AGM";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << AGM[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "MCCI";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << MCCI[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "AGF";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << AGF[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "OC";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << OC[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "OOC";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << OOC[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "AUPR";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << AUPR[i] << " ";
	os << std :: endl;
	os << std :: left << std :: setw(40) << "BCD";
	for (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << BCD[i] << " ";
	os << std :: endl;
}


template < typename Os >
void scorer :: print_overall_stats (Os & os)
{
	os << std :: left << std :: setw(40) << "overall_accuracy" << std :: setw(20) << overall_accuracy << std :: endl;
	os << std :: left << std :: setw(40) << "overall_random_accuracy_unbiased" << std :: setw(20) << overall_random_accuracy_unbiased << std :: endl;
	os << std :: left << std :: setw(40) << "overall_random_accuracy" << std :: setw(20) << overall_random_accuracy << std :: endl;
	os << std :: left << std :: setw(40) << "overall_kappa" << std :: setw(20) << overall_kappa << std :: endl;
	os << std :: left << std :: setw(40) << "PC_PI" << std :: setw(20) << PC_PI << std :: endl;
	os << std :: left << std :: setw(40) << "PC_AC1" << std :: setw(20) << PC_AC1 << std :: endl;
	os << std :: left << std :: setw(40) << "PC_S" << std :: setw(20) << PC_S << std :: endl;
	os << std :: left << std :: setw(40) << "PI" << std :: setw(20) << PI << std :: endl;
	os << std :: left << std :: setw(40) << "AC1" << std :: setw(20) << AC1 << std :: endl;
	os << std :: left << std :: setw(40) << "S" << std :: setw(20) << S << std :: endl;
	os << std :: left << std :: setw(40) << "kappa_SE" << std :: setw(20) << kappa_SE << std :: endl;
	os << std :: left << std :: setw(40) << "kappa_unbiased" << std :: setw(20) << kappa_unbiased << std :: endl;
	os << std :: left << std :: setw(40) << "kappa_no_prevalence" << std :: setw(20) << kappa_no_prevalence << std :: endl;
	os << std :: left << std :: setw(40) << "kappa_CI" << std :: setw(20) << kappa_CI << std :: endl;
	os << std :: left << std :: setw(40) << "overall_accuracy_se" << std :: setw(20) << overall_accuracy_se << std :: endl;
	os << std :: left << std :: setw(40) << "overall_accuracy_ci" << std :: setw(20) << overall_accuracy_ci << std :: endl;
	os << std :: left << std :: setw(40) << "chi_square" << std :: setw(20) << chi_square << std :: endl;
	os << std :: left << std :: setw(40) << "phi_square" << std :: setw(20) << phi_square << std :: endl;
	os << std :: left << std :: setw(40) << "cramers_V_calc" << std :: setw(20) << cramers_V_calc << std :: endl;
	os << std :: left << std :: setw(40) << "response_entropy" << std :: setw(20) << response_entropy << std :: endl;
	os << std :: left << std :: setw(40) << "reference_entropy" << std :: setw(20) << reference_entropy << std :: endl;
	os << std :: left << std :: setw(40) << "cross_entropy" << std :: setw(20) << cross_entropy << std :: endl;
	os << std :: left << std :: setw(40) << "join_entropy" << std :: setw(20) << join_entropy << std :: endl;
	os << std :: left << std :: setw(40) << "conditional_entropy" << std :: setw(20) << conditional_entropy << std :: endl;
	os << std :: left << std :: setw(40) << "mutual_information" << std :: setw(20) << mutual_information << std :: endl;
	os << std :: left << std :: setw(40) << "kl_divergence" << std :: setw(20) << kl_divergence << std :: endl;
	os << std :: left << std :: setw(40) << "lambda_B" << std :: setw(20) << lambda_B << std :: endl;
	os << std :: left << std :: setw(40) << "lambda_A" << std :: setw(20) << lambda_A << std :: endl;
	os << std :: left << std :: setw(40) << "DF" << std :: setw(20) << DF << std :: endl;
	os << std :: left << std :: setw(40) << "overall_jaccard_index" << std :: setw(20) << overall_jaccard_index << std :: endl;
	os << std :: left << std :: setw(40) << "hamming_loss" << std :: setw(20) << hamming_loss << std :: endl;
	os << std :: left << std :: setw(40) << "zero_one_loss" << std :: setw(20) << zero_one_loss << std :: endl;
	os << std :: left << std :: setw(40) << "NIR" << std :: setw(20) << NIR << std :: endl;
	os << std :: left << std :: setw(40) << "p_value" << std :: setw(20) << p_value << std :: endl;
	os << std :: left << std :: setw(40) << "overall_CEN" << std :: setw(20) << overall_CEN << std :: endl;
	os << std :: left << std :: setw(40) << "overall_MCEN" << std :: setw(20) << overall_MCEN << std :: endl;
	os << std :: left << std :: setw(40) << "overall_MCC" << std :: setw(20) << overall_MCC << std :: endl;
	os << std :: left << std :: setw(40) << "RR" << std :: setw(20) << RR << std :: endl;
	os << std :: left << std :: setw(40) << "CBA" << std :: setw(20) << CBA << std :: endl;
	os << std :: left << std :: setw(40) << "AUNU" << std :: setw(20) << AUNU << std :: endl;
	os << std :: left << std :: setw(40) << "AUNP" << std :: setw(20) << AUNP << std :: endl;
	os << std :: left << std :: setw(40) << "RCI" << std :: setw(20) << RCI << std :: endl;
	os << std :: left << std :: setw(40) << "overall_pearson_C" << std :: setw(20) << overall_pearson_C << std :: endl;
	os << std :: left << std :: setw(40) << "TPR_PPV_F1_micro" << std :: setw(20) << TPR_PPV_F1_micro << std :: endl;
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



#endif // __scorer_hpp__

