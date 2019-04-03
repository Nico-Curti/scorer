#ifndef SCORER_H
#define SCORER_H

#include <memory>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <assert.h>
#include <common_stats.h>
#include <class_stats.h>
#include <overall_stats.h>

struct scorer
{

	int Nclass;
	std::vector<float> classes;
	std::unique_ptr<float[]> confusion_matrix, TP, FN, FP, TN, POP, P, N, TOP, TON, TPR, TNR, PPV, NPV, FNR, FPR, FDR, FOR, ACC, F1_SCORE, F05_SCORE, F2_SCORE, MCC, BM, MK, PLR, NLR, DOR, PRE, G, RACC, ERR_ACC, RACCU, jaccard_index, IS, CEN, MCEN;
	float overall_accuracy, overall_random_accuracy_unbiased, overall_random_accuracy, overall_kappa, PC_PI, PC_AC1, PC_S, PI, AC1, S, kappa_SE, kappa_unbiased, kappa_no_prevalence, kappa_CI, overall_accuracy_se, chi_square, phi_square, cramers_V_calc, response_entropy, reference_entropy, cross_entropy, join_entropy, conditional_entropy, mutual_information, kl_divergence, lambda_B, lambda_A, DF, overall_jaccard_index, hamming_loss, zero_one_loss, NIR, p_value, overall_CEN, overall_MCEN;

	scorer(){};
	void compute_score(const int *lbl_true, const int *lbl_pred, const int &n_true, const int &n_pred)
	{

#ifdef PYTHONIC
#ifdef _OPENMP
#pragma omp parallel
	{
#endif
#endif
		assert(n_true == n_pred);
		auto n_lbl = n_true;
#ifdef _OPENMP
#pragma omp sections
		{
#endif

#ifdef _OPENMP
#pragma omp section
#endif
			this->classes = get_classes(lbl_true, lbl_pred, n_true, n_pred);

#ifdef _OPENMP
		}
#endif

		this->Nclass = static_cast<int>(classes.size());

#ifdef _OPENMP
#pragma omp sections
		{
#endif

#ifdef _OPENMP
#pragma omp section
#endif
			this->confusion_matrix = get_confusion_matrix(lbl_true, lbl_pred, n_lbl, this->classes.data(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->PC_S = get_PC_S(this->classes.data(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->DF = get_DF(this->classes.data(), Nclass);

#ifdef _OPENMP
		}
#endif

#ifdef _OPENMP
#pragma omp sections
		{
#endif

#ifdef _OPENMP
#pragma omp section
#endif
			this->TP = get_TP(this->confusion_matrix.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->FN = get_FN(this->confusion_matrix.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->FP = get_FP(this->confusion_matrix.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->TN = get_TN(this->confusion_matrix.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->CEN = get_CEN(this->classes.data(), this->confusion_matrix.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->MCEN = get_MCEN(this->classes.data(), this->confusion_matrix.get(), Nclass);

#ifdef _OPENMP
		}
#endif

#ifdef _OPENMP
#pragma omp sections
		{
#endif

#ifdef _OPENMP
#pragma omp section
#endif
			this->POP = get_POP(this->TP.get(), this->TN.get(), this->FP.get(), this->FN.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->P = get_P(this->TP.get(), this->FN.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->N = get_N(this->TN.get(), this->FP.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->TOP = get_TOP(this->TP.get(), this->FP.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->TON = get_TON(this->TN.get(), this->FN.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->TPR = get_TPR(this->TP.get(), this->FN.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->TNR = get_TNR(this->TN.get(), this->FP.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->PPV = get_PPV(this->TP.get(), this->FP.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->NPV = get_NPV(this->TN.get(), this->FN.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->ACC = get_ACC(this->TP.get(), this->FP.get(), this->FN.get(), this->TN.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->F1_SCORE = get_F1_SCORE(this->TP.get(), this->FP.get(), this->FN.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->F05_SCORE = get_F05_SCORE(this->TP.get(), this->FP.get(), this->FN.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->F2_SCORE = get_F2_SCORE(this->TP.get(), this->FP.get(), this->FN.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->MCC = get_MCC(this->TP.get(), this->TN.get(), this->FP.get(), this->FN.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->overall_CEN = get_overall_CEN(this->classes.data(), this->confusion_matrix.get(), this->CEN.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->overall_MCEN = get_overall_MCEN(this->classes.data(), this->confusion_matrix.get(), this->MCEN.get(), Nclass);

#ifdef _OPENMP
		}
#endif

#ifdef _OPENMP
#pragma omp sections
		{
#endif

#ifdef _OPENMP
#pragma omp section
#endif
			this->FNR = get_FNR(this->TPR.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->FPR = get_FPR(this->TNR.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->FDR = get_FDR(this->PPV.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->FOR = get_FOR(this->NPV.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->BM = get_BM(this->TPR.get(), this->TNR.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->MK = get_MK(this->PPV.get(), this->NPV.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->PRE = get_PRE(this->P.get(), this->POP.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->G = get_G(this->PPV.get(), this->TPR.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->RACC = get_RACC(this->TOP.get(), this->P.get(), this->POP.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->ERR_ACC = get_ERR_ACC(this->ACC.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->RACCU = get_RACCU(this->TOP.get(), this->P.get(), this->POP.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->jaccard_index = get_jaccard_index(this->TP.get(), this->TOP.get(), this->P.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->IS = get_IS(this->TP.get(), this->FP.get(), this->FN.get(), this->POP.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->overall_accuracy = get_overall_accuracy(this->TP.get(), this->POP.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->PC_PI = get_PC_PI(this->P.get(), this->TOP.get(), this->POP.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->PC_AC1 = get_PC_AC1(this->P.get(), this->TOP.get(), this->POP.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->chi_square = get_chi_square(this->classes.data(), this->confusion_matrix.get(), this->TOP.get(), this->P.get(), this->POP.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->response_entropy = get_response_entropy(this->TOP.get(), this->POP.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->reference_entropy = get_reference_entropy(this->P.get(), this->POP.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->cross_entropy = get_cross_entropy(this->TOP.get(), this->P.get(), this->POP.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->join_entropy = get_join_entropy(this->classes.data(), this->confusion_matrix.get(), this->POP.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->conditional_entropy = get_conditional_entropy(this->classes.data(), this->confusion_matrix.get(), this->P.get(), this->POP.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->kl_divergence = get_kl_divergence(this->P.get(), this->TOP.get(), this->POP.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->lambda_B = get_lambda_B(this->classes.data(), this->confusion_matrix.get(), this->TOP.get(), this->POP.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->lambda_A = get_lambda_A(this->classes.data(), this->confusion_matrix.get(), this->P.get(), this->POP.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->hamming_loss = get_hamming_loss(this->TP.get(), this->POP.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->zero_one_loss = get_zero_one_loss(this->TP.get(), this->POP.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->NIR = get_NIR(this->P.get(), this->POP.get(), Nclass);

#ifdef _OPENMP
		}
#endif

#ifdef _OPENMP
#pragma omp sections
		{
#endif

#ifdef _OPENMP
#pragma omp section
#endif
			this->PLR = get_PLR(this->TPR.get(), this->FPR.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->NLR = get_NLR(this->FNR.get(), this->TNR.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->overall_random_accuracy_unbiased = get_overall_random_accuracy_unbiased(this->RACCU.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->overall_random_accuracy = get_overall_random_accuracy(this->RACC.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->PI = get_PI(this->PC_PI, this->overall_accuracy);

#ifdef _OPENMP
#pragma omp section
#endif
			this->AC1 = get_AC1(this->PC_AC1, this->overall_accuracy);

#ifdef _OPENMP
#pragma omp section
#endif
			this->S = get_S(this->PC_S, this->overall_accuracy);

#ifdef _OPENMP
#pragma omp section
#endif
			this->kappa_no_prevalence = get_kappa_no_prevalence(this->overall_accuracy);

#ifdef _OPENMP
#pragma omp section
#endif
			this->overall_accuracy_se = get_overall_accuracy_se(this->overall_accuracy, this->POP.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->phi_square = get_phi_square(this->chi_square, this->POP.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->mutual_information = get_mutual_information(this->response_entropy, this->conditional_entropy);

#ifdef _OPENMP
#pragma omp section
#endif
			this->overall_jaccard_index = get_overall_jaccard_index(this->jaccard_index.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->p_value = get_p_value(this->TP.get(), this->POP.get(), Nclass, this->NIR);

#ifdef _OPENMP
		}
#endif

#ifdef _OPENMP
#pragma omp sections
		{
#endif

#ifdef _OPENMP
#pragma omp section
#endif
			this->DOR = get_DOR(this->PLR.get(), this->NLR.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->overall_kappa = get_overall_kappa(this->overall_random_accuracy, this->overall_accuracy);

#ifdef _OPENMP
#pragma omp section
#endif
			this->kappa_SE = get_kappa_SE(this->overall_accuracy, this->overall_random_accuracy, this->POP.get(), Nclass);

#ifdef _OPENMP
#pragma omp section
#endif
			this->kappa_unbiased = get_kappa_unbiased(this->overall_random_accuracy_unbiased, this->overall_accuracy);

#ifdef _OPENMP
#pragma omp section
#endif
			this->cramers_V_calc = get_cramers_V_calc(this->phi_square, this->classes.data(), Nclass);

#ifdef _OPENMP
		}
#endif

#ifdef _OPENMP
#pragma omp sections
		{
#endif

#ifdef _OPENMP
#pragma omp section
#endif
			this->kappa_CI = get_kappa_CI(this->overall_kappa, this->kappa_SE);

#ifdef _OPENMP
		}
#endif

#ifdef PYTHONIC
#ifdef _OPENMP
	}
#endif
#endif
	} // end computation function

	template<typename OS> void print_class_stats(OS &os)
	{

		os << std::left << std::setw(40) << "classes";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << classes[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "TP";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << TP[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "FN";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << FN[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "FP";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << FP[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "TN";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << TN[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "POP";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << POP[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "P";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << P[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "N";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << N[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "TOP";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << TOP[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "TON";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << TON[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "TPR";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << TPR[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "TNR";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << TNR[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "PPV";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << PPV[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "NPV";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << NPV[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "FNR";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << FNR[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "FPR";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << FPR[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "FDR";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << FDR[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "FOR";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << FOR[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "ACC";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << ACC[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "F1_SCORE";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << F1_SCORE[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "F05_SCORE";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << F05_SCORE[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "F2_SCORE";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << F2_SCORE[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "MCC";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << MCC[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "BM";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << BM[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "MK";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << MK[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "PLR";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << PLR[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "NLR";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << NLR[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "DOR";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << DOR[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "PRE";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << PRE[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "G";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << G[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "RACC";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << RACC[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "ERR_ACC";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << ERR_ACC[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "RACCU";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << RACCU[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "jaccard_index";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << jaccard_index[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "IS";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << IS[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "CEN";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << CEN[i] << " ";
		os << std::endl;
		os << std::left << std::setw(40) << "MCEN";
		for (int i = 0; i < this->Nclass; ++i) os << std::setw(20) << MCEN[i] << " ";
		os << std::endl;
	} // end print class_stats
	template<typename OS> void print_overall_stats(OS &os)
	{

		os << std::left << std::setw(40) << "overall_accuracy" << std::setw(20) << overall_accuracy << std::endl;

		os << std::left << std::setw(40) << "overall_random_accuracy_unbiased" << std::setw(20) << overall_random_accuracy_unbiased << std::endl;

		os << std::left << std::setw(40) << "overall_random_accuracy" << std::setw(20) << overall_random_accuracy << std::endl;

		os << std::left << std::setw(40) << "overall_kappa" << std::setw(20) << overall_kappa << std::endl;

		os << std::left << std::setw(40) << "PC_PI" << std::setw(20) << PC_PI << std::endl;

		os << std::left << std::setw(40) << "PC_AC1" << std::setw(20) << PC_AC1 << std::endl;

		os << std::left << std::setw(40) << "PC_S" << std::setw(20) << PC_S << std::endl;

		os << std::left << std::setw(40) << "PI" << std::setw(20) << PI << std::endl;

		os << std::left << std::setw(40) << "AC1" << std::setw(20) << AC1 << std::endl;

		os << std::left << std::setw(40) << "S" << std::setw(20) << S << std::endl;

		os << std::left << std::setw(40) << "kappa_SE" << std::setw(20) << kappa_SE << std::endl;

		os << std::left << std::setw(40) << "kappa_unbiased" << std::setw(20) << kappa_unbiased << std::endl;

		os << std::left << std::setw(40) << "kappa_no_prevalence" << std::setw(20) << kappa_no_prevalence << std::endl;

		os << std::left << std::setw(40) << "kappa_CI" << std::setw(20) << kappa_CI << std::endl;

		os << std::left << std::setw(40) << "overall_accuracy_se" << std::setw(20) << overall_accuracy_se << std::endl;

		os << std::left << std::setw(40) << "chi_square" << std::setw(20) << chi_square << std::endl;

		os << std::left << std::setw(40) << "phi_square" << std::setw(20) << phi_square << std::endl;

		os << std::left << std::setw(40) << "cramers_V_calc" << std::setw(20) << cramers_V_calc << std::endl;

		os << std::left << std::setw(40) << "response_entropy" << std::setw(20) << response_entropy << std::endl;

		os << std::left << std::setw(40) << "reference_entropy" << std::setw(20) << reference_entropy << std::endl;

		os << std::left << std::setw(40) << "cross_entropy" << std::setw(20) << cross_entropy << std::endl;

		os << std::left << std::setw(40) << "join_entropy" << std::setw(20) << join_entropy << std::endl;

		os << std::left << std::setw(40) << "conditional_entropy" << std::setw(20) << conditional_entropy << std::endl;

		os << std::left << std::setw(40) << "mutual_information" << std::setw(20) << mutual_information << std::endl;

		os << std::left << std::setw(40) << "kl_divergence" << std::setw(20) << kl_divergence << std::endl;

		os << std::left << std::setw(40) << "lambda_B" << std::setw(20) << lambda_B << std::endl;

		os << std::left << std::setw(40) << "lambda_A" << std::setw(20) << lambda_A << std::endl;

		os << std::left << std::setw(40) << "DF" << std::setw(20) << DF << std::endl;

		os << std::left << std::setw(40) << "overall_jaccard_index" << std::setw(20) << overall_jaccard_index << std::endl;

		os << std::left << std::setw(40) << "hamming_loss" << std::setw(20) << hamming_loss << std::endl;

		os << std::left << std::setw(40) << "zero_one_loss" << std::setw(20) << zero_one_loss << std::endl;

		os << std::left << std::setw(40) << "NIR" << std::setw(20) << NIR << std::endl;

		os << std::left << std::setw(40) << "p_value" << std::setw(20) << p_value << std::endl;

		os << std::left << std::setw(40) << "overall_CEN" << std::setw(20) << overall_CEN << std::endl;

		os << std::left << std::setw(40) << "overall_MCEN" << std::setw(20) << overall_MCEN << std::endl;

	} // end print overall_stats
	void print()
	{

		print_class_stats<std::ostream>(std::cout);
		std::cout << std::endl;
		print_overall_stats<std::ostream>(std::cout);

	} // end print function
	void dump(const std::string &filename)
	{

		std::ofstream os(filename + ".cl_stats");
		os << "Stats,"<<std::endl;
		print_class_stats<std::ofstream>(os);

		os.close();
		os.open(filename + ".ov_stats");
		os << "Stats,score" << std::endl;
		print_overall_stats<std::ofstream>(os);

		os.close();
	} // end dump function
}; // end struct

#endif // SCORER_H
