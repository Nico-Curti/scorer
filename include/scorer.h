#ifndef __scorer_h__
#define __scorer_h__

#include <memory>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_set>



struct scorer
{
	std :: unique_ptr < float[] > confusion_matrix;
	std :: unique_ptr < float[] > TP;
	std :: unique_ptr < float[] > FN;
	std :: unique_ptr < float[] > FP;
	std :: unique_ptr < float[] > TN;
	std :: unique_ptr < float[] > POP;
	std :: unique_ptr < float[] > P;
	std :: unique_ptr < float[] > N;
	std :: unique_ptr < float[] > TOP;
	std :: unique_ptr < float[] > TON;
	std :: unique_ptr < float[] > TPR;
	std :: unique_ptr < float[] > TNR;
	std :: unique_ptr < float[] > PPV;
	std :: unique_ptr < float[] > NPV;
	std :: unique_ptr < float[] > FNR;
	std :: unique_ptr < float[] > FPR;
	std :: unique_ptr < float[] > FDR;
	std :: unique_ptr < float[] > FOR;
	std :: unique_ptr < float[] > ACC;
	std :: unique_ptr < float[] > F1_SCORE;
	std :: unique_ptr < float[] > F05_SCORE;
	std :: unique_ptr < float[] > F2_SCORE;
	std :: unique_ptr < float[] > MCC;
	std :: unique_ptr < float[] > BM;
	std :: unique_ptr < float[] > MK;
	std :: unique_ptr < float[] > ICSI;
	std :: unique_ptr < float[] > PLR;
	std :: unique_ptr < float[] > NLR;
	std :: unique_ptr < float[] > DOR;
	std :: unique_ptr < float[] > PRE;
	std :: unique_ptr < float[] > G;
	std :: unique_ptr < float[] > RACC;
	std :: unique_ptr < float[] > ERR_ACC;
	std :: unique_ptr < float[] > RACCU;
	std :: unique_ptr < float[] > jaccard_index;
	std :: unique_ptr < float[] > IS;
	std :: unique_ptr < float[] > CEN;
	std :: unique_ptr < float[] > MCEN;
	std :: unique_ptr < float[] > AUC;
	std :: unique_ptr < float[] > dIND;
	std :: unique_ptr < float[] > sIND;
	std :: unique_ptr < float[] > DP;
	std :: unique_ptr < float[] > Y;
	std :: unique_ptr < float[] > PLRI;
	std :: unique_ptr < float[] > NLRI;
	std :: unique_ptr < float[] > DPI;
	std :: unique_ptr < float[] > AUCI;
	std :: unique_ptr < float[] > GI;
	std :: unique_ptr < float[] > LS;
	std :: unique_ptr < float[] > AM;
	std :: unique_ptr < float[] > OP;
	std :: unique_ptr < float[] > IBA;
	std :: unique_ptr < float[] > GM;
	std :: unique_ptr < float[] > Q;
	std :: unique_ptr < float[] > AGM;
	std :: unique_ptr < float[] > MCCI;
	std :: unique_ptr < float[] > AGF;
	std :: unique_ptr < float[] > OC;
	std :: unique_ptr < float[] > OOC;
	std :: unique_ptr < float[] > AUPR;
	std :: unique_ptr < float[] > BCD;
	float overall_accuracy;
	float overall_random_accuracy_unbiased;
	float overall_random_accuracy;
	float overall_kappa;
	float PC_PI;
	float PC_AC1;
	float PC_S;
	float PI;
	float AC1;
	float S;
	float kappa_SE;
	float kappa_unbiased;
	float kappa_no_prevalence;
	float kappa_CI_up;
	float kappa_CI_down;
	float overall_accuracy_se;
	float overall_accuracy_ci_up;
	float overall_accuracy_ci_down;
	float chi_square;
	float phi_square;
	float cramer_V;
	float response_entropy;
	float reference_entropy;
	float cross_entropy;
	float join_entropy;
	float conditional_entropy;
	float mutual_information;
	float kl_divergence;
	float lambda_B;
	float lambda_A;
	float DF;
	float overall_jaccard_index;
	float hamming_loss;
	float zero_one_loss;
	float NIR;
	float p_value;
	float overall_CEN;
	float overall_MCEN;
	float overall_MCC;
	float RR;
	float CBA;
	float AUNU;
	float AUNP;
	float RCI;
	float CSI;
	float overall_pearson_C;
	float TPR_PPV_F1_micro;
	float MCC_analysis;
	float kappa_analysis_cicchetti;
	float kappa_analysis_koch;
	float kappa_analysis_fleiss;
	float kappa_analysis_altman;
	float V_analysis;
	float TPR_macro;
	float PPV_macro;
	float ACC_macro;
	float F1_macro;

	std :: vector < float > classes;

	int Nclass;

	scorer ();

	~scorer () = default;

	// Members

	void compute_score (const int * lbl_true, const int * lbl_pred, const int & n_true, const int & n_pred);


	template < typename Os >
	void print_class_stats (Os & os);


	template < typename Os >
	void print_overall_stats (Os & os);


	void print ();


	void dump (const std :: string & filename);


	template < typename dtype >
	int * encoder (dtype * arr, const int & size);

};


#endif // __scorer_h__

