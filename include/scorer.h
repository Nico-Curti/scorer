#ifndef __scorer_h__
#define __scorer_h__

#include <memory>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <vector>



struct scorer
{

	std :: vector < float > classes;
	std :: unique_ptr < float[] > confusion_matrix, TP, FN, FP, TN, POP, P, N, TOP, TON, TPR, TNR, PPV, NPV, FNR, FPR, FDR, FOR, ACC, F1_SCORE, F05_SCORE, F2_SCORE, MCC, BM, MK, PLR, NLR, DOR, PRE, G, RACC, ERR_ACC, RACCU, jaccard_index, IS, CEN, MCEN, AUC, dIND, sIND, DP, Y, PLRI, NLRI, DPI, AUCI, GI, LS, AM, OP, IBA, GM, Q, AGM, MCCI, AGF, OC, OOC, AUPR, BCD;
	float overall_accuracy, overall_random_accuracy_unbiased, overall_random_accuracy, overall_kappa, PC_PI, PC_AC1, PC_S, PI, AC1, S, kappa_SE, kappa_unbiased, kappa_no_prevalence, kappa_CI, overall_accuracy_se, overall_accuracy_ci, chi_square, phi_square, cramers_V_calc, response_entropy, reference_entropy, cross_entropy, join_entropy, conditional_entropy, mutual_information, kl_divergence, lambda_B, lambda_A, DF, overall_jaccard_index, hamming_loss, zero_one_loss, NIR, p_value, overall_CEN, overall_MCEN, overall_MCC, RR, CBA, AUNU, AUNP, RCI, overall_pearson_C, TPR_PPV_F1_micro;

	int Nclass;

	scorer ();

	//Members

	void compute_score (const int * lbl_true, const int * lbl_pred, const int & n_true, const int & n_pred);

	template < typename Os >
	void print_class_stats (Os & os);

	template < typename Os >
	void print_overall_stats (Os & os);

	void print ();

	void dump (const std :: string & filename);

};


#endif // __scorer_h__

