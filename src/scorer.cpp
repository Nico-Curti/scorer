#include <scorer.hpp>
#include <common_stats.h>
#include <class_stats.h>
#include <overall_stats.h>


scorer :: scorer ()
{
}


void scorer :: compute_score (const int * lbl_true, const int * lbl_pred, const int & n_true, const int & n_pred)
{
#ifdef __pythonic__
#ifdef _OPENMP
#pragma omp parallel
	{
#endif
#endif

	assert (n_true == n_pred);
	auto n_lbl = n_true;
#ifdef _OPENMP
#pragma omp sections
	{
#endif

#ifdef _OPENMP
#pragma omp section
#endif
		this->classes = get_classes ( lbl_true, lbl_pred, n_true, n_pred );

#ifdef _OPENMP
	}
#endif


	this->Nclass = static_cast < int >(classes.size());

	if ( this->Nclass == 1 )
	{
#ifdef _OPENMP
#pragma omp single
#endif
		std :: cerr << "Nclass must be greater than 1" << std :: endl;
		std :: exit(1);
	}
#ifdef _OPENMP
#pragma omp sections
	{
#endif

#ifdef _OPENMP
#pragma omp section
#endif
		this->DF = get_DF ( this->classes.data(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->PC_S = get_PC_S ( this->classes.data(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->confusion_matrix = get_confusion_matrix ( lbl_true, lbl_pred, n_lbl, this->classes.data(), this->Nclass );

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
		this->MCEN = get_MCEN ( this->confusion_matrix.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->CEN = get_CEN ( this->confusion_matrix.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->TN = get_TN ( this->confusion_matrix.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->FP = get_FP ( this->confusion_matrix.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->FN = get_FN ( this->confusion_matrix.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->TP = get_TP ( this->confusion_matrix.get(), this->Nclass );

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
		this->TNR = get_TNR ( this->TN.get(), this->FP.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->N = get_N ( this->TN.get(), this->FP.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->NPV = get_NPV ( this->TN.get(), this->FN.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->TON = get_TON ( this->TN.get(), this->FN.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->TPR_PPV_F1_micro = get_TPR_PPV_F1_micro ( this->TP.get(), this->FN.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->AGF = get_AGF ( this->TP.get(), this->FP.get(), this->FN.get(), this->TN.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->Q = get_Q ( this->TP.get(), this->TN.get(), this->FP.get(), this->FN.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->MCC = get_MCC ( this->TP.get(), this->TN.get(), this->FP.get(), this->FN.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->F2_SCORE = get_F2_SCORE ( this->TP.get(), this->FP.get(), this->FN.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->F05_SCORE = get_F05_SCORE ( this->TP.get(), this->FP.get(), this->FN.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->F1_SCORE = get_F1_SCORE ( this->TP.get(), this->FP.get(), this->FN.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->ACC = get_ACC ( this->TP.get(), this->FP.get(), this->FN.get(), this->TN.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->PPV = get_PPV ( this->TP.get(), this->FP.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->TPR = get_TPR ( this->TP.get(), this->FN.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->TOP = get_TOP ( this->TP.get(), this->FP.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->P = get_P ( this->TP.get(), this->FN.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->POP = get_POP ( this->TP.get(), this->TN.get(), this->FP.get(), this->FN.get(), this->Nclass );

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
		this->FPR = get_FPR ( this->TNR.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->FOR = get_FOR ( this->NPV.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->MCCI = get_MCCI ( this->MCC.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->F1_macro = get_F1_macro ( this->F1_SCORE.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->ACC_macro = get_ACC_macro ( this->ACC.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->ERR_ACC = get_ERR_ACC ( this->ACC.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->PPV_macro = get_PPV_macro ( this->PPV.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->MK = get_MK ( this->PPV.get(), this->NPV.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->FDR = get_FDR ( this->PPV.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->TPR_macro = get_TPR_macro ( this->TPR.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->AUPR = get_AUPR ( this->PPV.get(), this->TPR.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->GM = get_GM ( this->TNR.get(), this->TPR.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->IBA = get_IBA ( this->TPR.get(), this->TNR.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->OP = get_OP ( this->ACC.get(), this->TPR.get(), this->TNR.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->DP = get_DP ( this->TPR.get(), this->TNR.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->dIND = get_dIND ( this->TNR.get(), this->TPR.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->AUC = get_AUC ( this->TNR.get(), this->TPR.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->G = get_G ( this->PPV.get(), this->TPR.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->ICSI = get_ICSI ( this->PPV.get(), this->TPR.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->BM = get_BM ( this->TPR.get(), this->TNR.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->FNR = get_FNR ( this->TPR.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->RR = get_RR ( this->TOP.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->CBA = get_CBA ( this->confusion_matrix.get(), this->TOP.get(), this->P.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->overall_MCC = get_overall_MCC ( this->confusion_matrix.get(), this->TOP.get(), this->P.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->overall_MCEN = get_overall_MCEN ( this->TP.get(), this->TOP.get(), this->P.get(), this->MCEN.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->overall_CEN = get_overall_CEN ( this->TOP.get(), this->P.get(), this->CEN.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->OOC = get_OOC ( this->TP.get(), this->TOP.get(), this->P.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->OC = get_OC ( this->TP.get(), this->TOP.get(), this->P.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->AM = get_AM ( this->TOP.get(), this->P.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->jaccard_index = get_jaccard_index ( this->TP.get(), this->TOP.get(), this->P.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->NIR = get_NIR ( this->P.get(), this->POP.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->zero_one_loss = get_zero_one_loss ( this->TP.get(), this->POP.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->hamming_loss = get_hamming_loss ( this->TP.get(), this->POP.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->lambda_A = get_lambda_A ( this->confusion_matrix.get(), this->P.get(), this->POP.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->lambda_B = get_lambda_B ( this->confusion_matrix.get(), this->TOP.get(), this->POP.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->kl_divergence = get_kl_divergence ( this->P.get(), this->TOP.get(), this->POP.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->conditional_entropy = get_conditional_entropy ( this->confusion_matrix.get(), this->P.get(), this->POP.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->join_entropy = get_join_entropy ( this->confusion_matrix.get(), this->POP.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->cross_entropy = get_cross_entropy ( this->TOP.get(), this->P.get(), this->POP.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->reference_entropy = get_reference_entropy ( this->P.get(), this->POP.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->response_entropy = get_response_entropy ( this->TOP.get(), this->POP.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->chi_square = get_chi_square ( this->confusion_matrix.get(), this->TOP.get(), this->P.get(), this->POP.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->PC_AC1 = get_PC_AC1 ( this->P.get(), this->TOP.get(), this->POP.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->PC_PI = get_PC_PI ( this->P.get(), this->TOP.get(), this->POP.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->overall_accuracy = get_overall_accuracy ( this->TP.get(), this->POP.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->IS = get_IS ( this->TP.get(), this->FP.get(), this->FN.get(), this->POP.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->RACCU = get_RACCU ( this->TOP.get(), this->P.get(), this->POP.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->RACC = get_RACC ( this->TOP.get(), this->P.get(), this->POP.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->PRE = get_PRE ( this->P.get(), this->POP.get(), this->Nclass );

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
		this->DPI = get_DPI ( this->DP.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->sIND = get_sIND ( this->dIND.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->AUNU = get_AUNU ( this->AUC.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->GI = get_GI ( this->AUC.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->AUCI = get_AUCI ( this->AUC.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->PLR = get_PLR ( this->TPR.get(), this->FPR.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->CSI = get_CSI ( this->ICSI.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->Y = get_Y ( this->BM.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->NLR = get_NLR ( this->FNR.get(), this->TNR.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->MCC_analysis = get_MCC_analysis ( this->overall_MCC );

#ifdef _OPENMP
#pragma omp section
#endif
		this->BCD = get_BCD ( this->TOP.get(), this->P.get(), this->AM.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->overall_jaccard_index = get_overall_jaccard_index ( this->jaccard_index.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->AUNP = get_AUNP ( this->P.get(), this->POP.get(), this->AUC.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->p_value = get_p_value ( this->TP.get(), this->POP.get(), this->Nclass, this->NIR );

#ifdef _OPENMP
#pragma omp section
#endif
		this->mutual_information = get_mutual_information ( this->response_entropy, this->conditional_entropy );

#ifdef _OPENMP
#pragma omp section
#endif
		this->overall_pearson_C = get_overall_pearson_C ( this->chi_square, this->POP.get() );

#ifdef _OPENMP
#pragma omp section
#endif
		this->phi_square = get_phi_square ( this->chi_square, this->POP.get() );

#ifdef _OPENMP
#pragma omp section
#endif
		this->overall_accuracy_se = get_overall_accuracy_se ( this->overall_accuracy, this->POP.get() );

#ifdef _OPENMP
#pragma omp section
#endif
		this->kappa_no_prevalence = get_kappa_no_prevalence ( this->overall_accuracy );

#ifdef _OPENMP
#pragma omp section
#endif
		this->S = get_S ( this->PC_S, this->overall_accuracy );

#ifdef _OPENMP
#pragma omp section
#endif
		this->AC1 = get_AC1 ( this->PC_AC1, this->overall_accuracy );

#ifdef _OPENMP
#pragma omp section
#endif
		this->PI = get_PI ( this->PC_PI, this->overall_accuracy );

#ifdef _OPENMP
#pragma omp section
#endif
		this->AGM = get_AGM ( this->TPR.get(), this->TNR.get(), this->GM.get(), this->N.get(), this->POP.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->overall_random_accuracy_unbiased = get_overall_random_accuracy_unbiased ( this->RACCU.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->overall_random_accuracy = get_overall_random_accuracy ( this->RACC.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->LS = get_LS ( this->PPV.get(), this->PRE.get(), this->Nclass );

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
		this->PLRI = get_PLRI ( this->PLR.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->NLRI = get_NLRI ( this->NLR.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->DOR = get_DOR ( this->PLR.get(), this->NLR.get(), this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->RCI = get_RCI ( this->mutual_information, this->reference_entropy );

#ifdef _OPENMP
#pragma omp section
#endif
		this->cramer_V = get_cramer_V ( this->phi_square, this->Nclass );

#ifdef _OPENMP
#pragma omp section
#endif
		this->overall_accuracy_ci_down = get_overall_accuracy_ci_down ( this->overall_accuracy, this->overall_accuracy_se );

#ifdef _OPENMP
#pragma omp section
#endif
		this->overall_accuracy_ci_up = get_overall_accuracy_ci_up ( this->overall_accuracy, this->overall_accuracy_se );

#ifdef _OPENMP
#pragma omp section
#endif
		this->kappa_unbiased = get_kappa_unbiased ( this->overall_random_accuracy_unbiased, this->overall_accuracy );

#ifdef _OPENMP
#pragma omp section
#endif
		this->kappa_SE = get_kappa_SE ( this->overall_accuracy, this->overall_random_accuracy, this->POP.get() );

#ifdef _OPENMP
#pragma omp section
#endif
		this->overall_kappa = get_overall_kappa ( this->overall_random_accuracy, this->overall_accuracy );

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
		this->V_analysis = get_V_analysis ( this->cramer_V );

#ifdef _OPENMP
#pragma omp section
#endif
		this->kappa_analysis_altman = get_kappa_analysis_altman ( this->overall_kappa );

#ifdef _OPENMP
#pragma omp section
#endif
		this->kappa_analysis_fleiss = get_kappa_analysis_fleiss ( this->overall_kappa );

#ifdef _OPENMP
#pragma omp section
#endif
		this->kappa_analysis_koch = get_kappa_analysis_koch ( this->overall_kappa );

#ifdef _OPENMP
#pragma omp section
#endif
		this->kappa_analysis_cicchetti = get_kappa_analysis_cicchetti ( this->overall_kappa );

#ifdef _OPENMP
#pragma omp section
#endif
		this->kappa_CI_down = get_kappa_CI_down ( this->overall_kappa, this->kappa_SE );

#ifdef _OPENMP
#pragma omp section
#endif
		this->kappa_CI_up = get_kappa_CI_up ( this->overall_kappa, this->kappa_SE );

#ifdef _OPENMP
	}
#endif


#ifdef __pythonic__
#ifdef _OPENMP
	} // end computation function
#endif
#endif


}


