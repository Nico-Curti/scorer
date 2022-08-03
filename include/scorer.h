/* This file was automatically generated */
/* Any change will be lost in the next build */

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



/**
* @class scorer
* @brief Abstract type which stores the full list of scores and allows their evaluation using parallel environment
*
* @details Each member of the class represents a different score (class statistics and overall statistics).
*
*/
struct scorer
{
	std :: unique_ptr < float[] > confusion_matrix; ///< confusion_matrix array
	std :: unique_ptr < float[] > TP; ///< TP array
	std :: unique_ptr < float[] > FN; ///< FN array
	std :: unique_ptr < float[] > FP; ///< FP array
	std :: unique_ptr < float[] > TN; ///< TN array
	std :: unique_ptr < float[] > POP; ///< POP array
	std :: unique_ptr < float[] > P; ///< P array
	std :: unique_ptr < float[] > N; ///< N array
	std :: unique_ptr < float[] > TOP; ///< TOP array
	std :: unique_ptr < float[] > TON; ///< TON array
	std :: unique_ptr < float[] > TPR; ///< TPR array
	std :: unique_ptr < float[] > TNR; ///< TNR array
	std :: unique_ptr < float[] > PPV; ///< PPV array
	std :: unique_ptr < float[] > NPV; ///< NPV array
	std :: unique_ptr < float[] > FNR; ///< FNR array
	std :: unique_ptr < float[] > FPR; ///< FPR array
	std :: unique_ptr < float[] > FDR; ///< FDR array
	std :: unique_ptr < float[] > FOR; ///< FOR array
	std :: unique_ptr < float[] > ACC; ///< ACC array
	std :: unique_ptr < float[] > F1_SCORE; ///< F1_SCORE array
	std :: unique_ptr < float[] > F05_SCORE; ///< F05_SCORE array
	std :: unique_ptr < float[] > F2_SCORE; ///< F2_SCORE array
	std :: unique_ptr < float[] > MCC; ///< MCC array
	std :: unique_ptr < float[] > BM; ///< BM array
	std :: unique_ptr < float[] > MK; ///< MK array
	std :: unique_ptr < float[] > ICSI; ///< ICSI array
	std :: unique_ptr < float[] > PLR; ///< PLR array
	std :: unique_ptr < float[] > NLR; ///< NLR array
	std :: unique_ptr < float[] > DOR; ///< DOR array
	std :: unique_ptr < float[] > PRE; ///< PRE array
	std :: unique_ptr < float[] > G; ///< G array
	std :: unique_ptr < float[] > RACC; ///< RACC array
	std :: unique_ptr < float[] > ERR_ACC; ///< ERR_ACC array
	std :: unique_ptr < float[] > RACCU; ///< RACCU array
	std :: unique_ptr < float[] > jaccard_index; ///< jaccard_index array
	std :: unique_ptr < float[] > IS; ///< IS array
	std :: unique_ptr < float[] > CEN; ///< CEN array
	std :: unique_ptr < float[] > MCEN; ///< MCEN array
	std :: unique_ptr < float[] > AUC; ///< AUC array
	std :: unique_ptr < float[] > dIND; ///< dIND array
	std :: unique_ptr < float[] > sIND; ///< sIND array
	std :: unique_ptr < float[] > DP; ///< DP array
	std :: unique_ptr < float[] > Y; ///< Y array
	std :: unique_ptr < float[] > PLRI; ///< PLRI array
	std :: unique_ptr < float[] > NLRI; ///< NLRI array
	std :: unique_ptr < float[] > DPI; ///< DPI array
	std :: unique_ptr < float[] > AUCI; ///< AUCI array
	std :: unique_ptr < float[] > GI; ///< GI array
	std :: unique_ptr < float[] > LS; ///< LS array
	std :: unique_ptr < float[] > AM; ///< AM array
	std :: unique_ptr < float[] > OP; ///< OP array
	std :: unique_ptr < float[] > IBA; ///< IBA array
	std :: unique_ptr < float[] > GM; ///< GM array
	std :: unique_ptr < float[] > Q; ///< Q array
	std :: unique_ptr < float[] > AGM; ///< AGM array
	std :: unique_ptr < float[] > MCCI; ///< MCCI array
	std :: unique_ptr < float[] > AGF; ///< AGF array
	std :: unique_ptr < float[] > OC; ///< OC array
	std :: unique_ptr < float[] > OOC; ///< OOC array
	std :: unique_ptr < float[] > AUPR; ///< AUPR array
	std :: unique_ptr < float[] > BCD; ///< BCD array
	float overall_accuracy; ///< overall_accuracy value
	float overall_random_accuracy_unbiased; ///< overall_random_accuracy_unbiased value
	float overall_random_accuracy; ///< overall_random_accuracy value
	float overall_kappa; ///< overall_kappa value
	float PC_PI; ///< PC_PI value
	float PC_AC1; ///< PC_AC1 value
	float PC_S; ///< PC_S value
	float PI; ///< PI value
	float AC1; ///< AC1 value
	float S; ///< S value
	float kappa_SE; ///< kappa_SE value
	float kappa_unbiased; ///< kappa_unbiased value
	float kappa_no_prevalence; ///< kappa_no_prevalence value
	float kappa_CI_up; ///< kappa_CI_up value
	float kappa_CI_down; ///< kappa_CI_down value
	float overall_accuracy_se; ///< overall_accuracy_se value
	float overall_accuracy_ci_up; ///< overall_accuracy_ci_up value
	float overall_accuracy_ci_down; ///< overall_accuracy_ci_down value
	float chi_square; ///< chi_square value
	float phi_square; ///< phi_square value
	float cramer_V; ///< cramer_V value
	float response_entropy; ///< response_entropy value
	float reference_entropy; ///< reference_entropy value
	float cross_entropy; ///< cross_entropy value
	float join_entropy; ///< join_entropy value
	float conditional_entropy; ///< conditional_entropy value
	float mutual_information; ///< mutual_information value
	float kl_divergence; ///< kl_divergence value
	float lambda_B; ///< lambda_B value
	float lambda_A; ///< lambda_A value
	float DF; ///< DF value
	float overall_jaccard_index; ///< overall_jaccard_index value
	float hamming_loss; ///< hamming_loss value
	float zero_one_loss; ///< zero_one_loss value
	float NIR; ///< NIR value
	float p_value; ///< p_value value
	float overall_CEN; ///< overall_CEN value
	float overall_MCEN; ///< overall_MCEN value
	float overall_MCC; ///< overall_MCC value
	float RR; ///< RR value
	float CBA; ///< CBA value
	float AUNU; ///< AUNU value
	float AUNP; ///< AUNP value
	float RCI; ///< RCI value
	float CSI; ///< CSI value
	float overall_pearson_C; ///< overall_pearson_C value
	float TPR_PPV_F1_micro; ///< TPR_PPV_F1_micro value
	float MCC_analysis; ///< MCC_analysis value
	float kappa_analysis_cicchetti; ///< kappa_analysis_cicchetti value
	float kappa_analysis_koch; ///< kappa_analysis_koch value
	float kappa_analysis_fleiss; ///< kappa_analysis_fleiss value
	float kappa_analysis_altman; ///< kappa_analysis_altman value
	float V_analysis; ///< V_analysis value
	float TPR_macro; ///< TPR_macro value
	float PPV_macro; ///< PPV_macro value
	float ACC_macro; ///< ACC_macro value
	float F1_macro; ///< F1_macro value

	std :: vector < float > classes; ///< array of classes

	int32_t Nclass; ///< number of classes

	/**
	* @brief Default constructor.
	*
	*/
	scorer ();

	/**
	* @brief Default destructor.
	*
	*/
	~scorer () = default;

	// Members

	/**
	* @brief Compute the available scores related to the input labels. This is the core function of the object.
	*
	* @param lbl_true array of true labels
	* @param lbl_pred array of predicted labels
	* @param n_true size of the array lbl_true (aka number of true labels)
	* @param n_pred size of the array lbl_pred (aka number of predicted labels)
	*
	*/
	void compute_score (const int32_t * lbl_true, const int32_t * lbl_pred, const int32_t & n_true, const int32_t & n_pred);


	/**
	* @brief Print the scores related to class statistics, i.e a score for each class. The output is a table in which each score is represented by a row.
	*
	* @tparam Os output stream data type
	* @param os ostream (es. std :: cout)
	*
	*/
	template < typename Os >
	void print_class_stats (Os & os);


	/**
	* @brief Print the scores related to overall statistics, i.e a global score among classes. The output is a table in which each score is represented by a row.
	*
	* @tparam Os output stream data type
	* @param os ostream (es. std :: cout)
	*
	*/
	template < typename Os >
	void print_overall_stats (Os & os);


	/**
	* @brief Print the full list of scores, i.e the class statistics followed by the overall statistics.
	*
	*/
	void print ();


	/**
	* @brief Dump the statistics to file. The file will save only the class statistics in csv format.
	*
	* @param filename Output filename or path
	*
	*/
	void dump (const std :: string & filename);


	/**
	* @brief Convert/Encode the input labels from any type to int (categorical).
	*
	* @tparam dtype Any "simple" type in which the label are stored.
	* @param arr Array of input labels.
	* @param size Lenght of the input array.
	*
	*/
	template < typename dtype >
	int32_t * encoder (dtype * arr, const int32_t & size);

};


#endif // __scorer_h__

