# distutils: language = c++
# cython: language_level=2

from cython.operator cimport dereference as deref
from libcpp.memory cimport unique_ptr

from scorer cimport scorer

cdef class _scorer:

  def __init__ (self):
    self.thisptr.reset(new scorer())


  def evaluate (self, int[::1] lbl_true, int[::1] lbl_pred, int n_lbl):
    deref(self.thisptr).compute_score(&lbl_true[0], &lbl_pred[0], n_lbl, n_lbl)

    self.Nclass = deref(self.thisptr).classes.size()

    score = {
              'Classes': deref(self.thisptr).classes,
              'Confusion Matrix': [int((deref(self.thisptr).confusion_matrix.get())[i]) for i in range(self.Nclass * self.Nclass)],
              'TP(True positive/hit)' : [(deref(self.thisptr).TP.get())[i] for i in range(self.Nclass)],
              'FN(False negative/miss/type 2 error)' : [(deref(self.thisptr).FN.get())[i] for i in range(self.Nclass)],
              'FP(False positive/type 1 error/false alarm)' : [(deref(self.thisptr).FP.get())[i] for i in range(self.Nclass)],
              'TN(True negative/correct rejection)' : [(deref(self.thisptr).TN.get())[i] for i in range(self.Nclass)],
              'POP(Population)' : [(deref(self.thisptr).POP.get())[i] for i in range(self.Nclass)],
              'P(Condition positive or support)' : [(deref(self.thisptr).P.get())[i] for i in range(self.Nclass)],
              'N(Condition negative)' : [(deref(self.thisptr).N.get())[i] for i in range(self.Nclass)],
              'TOP(Test outcome positive)' : [(deref(self.thisptr).TOP.get())[i] for i in range(self.Nclass)],
              'TON(Test outcome negative)' : [(deref(self.thisptr).TON.get())[i] for i in range(self.Nclass)],
              'TPR(Sensitivity / recall / hit rate / true positive rate)' : [(deref(self.thisptr).TPR.get())[i] for i in range(self.Nclass)],
              'TNR(Specificity or true negative rate)' : [(deref(self.thisptr).TNR.get())[i] for i in range(self.Nclass)],
              'PPV(Precision or positive predictive value)' : [(deref(self.thisptr).PPV.get())[i] for i in range(self.Nclass)],
              'NPV(Negative predictive value)' : [(deref(self.thisptr).NPV.get())[i] for i in range(self.Nclass)],
              'FNR(Miss rate or false negative rate)' : [(deref(self.thisptr).FNR.get())[i] for i in range(self.Nclass)],
              'FPR(Fall-out or false positive rate)' : [(deref(self.thisptr).FPR.get())[i] for i in range(self.Nclass)],
              'FDR(False discovery rate)' : [(deref(self.thisptr).FDR.get())[i] for i in range(self.Nclass)],
              'FOR(False omission rate)' : [(deref(self.thisptr).FOR.get())[i] for i in range(self.Nclass)],
              'ACC(Accuracy)' : [(deref(self.thisptr).ACC.get())[i] for i in range(self.Nclass)],
              'F1(F1 score - harmonic mean of precision and sensitivity)' : [(deref(self.thisptr).F1_SCORE.get())[i] for i in range(self.Nclass)],
              'F0.5(F0.5 score)' : [(deref(self.thisptr).F05_SCORE.get())[i] for i in range(self.Nclass)],
              'F2(F2 score)' : [(deref(self.thisptr).F2_SCORE.get())[i] for i in range(self.Nclass)],
              'MCC(Matthews correlation coefficient)' : [(deref(self.thisptr).MCC.get())[i] for i in range(self.Nclass)],
              'BM(Informedness or bookmaker informedness)' : [(deref(self.thisptr).BM.get())[i] for i in range(self.Nclass)],
              'MK(Markedness)' : [(deref(self.thisptr).MK.get())[i] for i in range(self.Nclass)],
              'ICSI(Individual classification success index)' : [(deref(self.thisptr).ICSI.get())[i] for i in range(self.Nclass)],
              'PLR(Positive likelihood ratio)' : [(deref(self.thisptr).PLR.get())[i] for i in range(self.Nclass)],
              'NLR(Negative likelihood ratio)' : [(deref(self.thisptr).NLR.get())[i] for i in range(self.Nclass)],
              'DOR(Diagnostic odds ratio)' : [(deref(self.thisptr).DOR.get())[i] for i in range(self.Nclass)],
              'PRE(Prevalence)' : [(deref(self.thisptr).PRE.get())[i] for i in range(self.Nclass)],
              'G(G-measure geometric mean of precision and sensitivity)' : [(deref(self.thisptr).G.get())[i] for i in range(self.Nclass)],
              'RACC(Random accuracy)' : [(deref(self.thisptr).RACC.get())[i] for i in range(self.Nclass)],
              'ERR(Error rate)' : [(deref(self.thisptr).ERR_ACC.get())[i] for i in range(self.Nclass)],
              'RACCU(Random accuracy unbiased)' : [(deref(self.thisptr).RACCU.get())[i] for i in range(self.Nclass)],
              'J(Jaccard index)' : [(deref(self.thisptr).jaccard_index.get())[i] for i in range(self.Nclass)],
              'IS(Information score)' : [(deref(self.thisptr).IS.get())[i] for i in range(self.Nclass)],
              'CEN(Confusion entropy)' : [(deref(self.thisptr).CEN.get())[i] for i in range(self.Nclass)],
              'MCEN(Modified confusion entropy)' : [(deref(self.thisptr).MCEN.get())[i] for i in range(self.Nclass)],
              'AUC(Area Under the ROC curve)' : [(deref(self.thisptr).AUC.get())[i] for i in range(self.Nclass)],
              'dInd(Distance index)' : [(deref(self.thisptr).dIND.get())[i] for i in range(self.Nclass)],
              'sInd(Similarity index)' : [(deref(self.thisptr).sIND.get())[i] for i in range(self.Nclass)],
              'DP(Discriminant power)' : [(deref(self.thisptr).DP.get())[i] for i in range(self.Nclass)],
              'Y(Youden index)' : [(deref(self.thisptr).Y.get())[i] for i in range(self.Nclass)],
              'PLRI(Positive likelihood ratio interpretation)' : [(deref(self.thisptr).PLRI.get())[i] for i in range(self.Nclass)],
              'NLRI(Negative likelihood ratio interpretation)' : [(deref(self.thisptr).NLRI.get())[i] for i in range(self.Nclass)],
              'DPI(Discriminant power interpretation)' : [(deref(self.thisptr).DPI.get())[i] for i in range(self.Nclass)],
              'AUCI(AUC value interpretation)' : [(deref(self.thisptr).AUCI.get())[i] for i in range(self.Nclass)],
              'GI(Gini index)' : [(deref(self.thisptr).GI.get())[i] for i in range(self.Nclass)],
              'LS(Lift score)' : [(deref(self.thisptr).LS.get())[i] for i in range(self.Nclass)],
              'AM(Difference between automatic and manual classification)' : [(deref(self.thisptr).AM.get())[i] for i in range(self.Nclass)],
              'OP(Optimized precision)' : [(deref(self.thisptr).OP.get())[i] for i in range(self.Nclass)],
              'IBA(Index of balanced accuracy)' : [(deref(self.thisptr).IBA.get())[i] for i in range(self.Nclass)],
              'GM(G-mean geometric mean of specificity and sensitivity)' : [(deref(self.thisptr).GM.get())[i] for i in range(self.Nclass)],
              'Q(Yule Q - coefficient of colligation)' : [(deref(self.thisptr).Q.get())[i] for i in range(self.Nclass)],
              'AGM(Adjusted geometric mean)' : [(deref(self.thisptr).AGM.get())[i] for i in range(self.Nclass)],
              'MCCI(Matthews correlation coefficient interpretation)' : [(deref(self.thisptr).MCCI.get())[i] for i in range(self.Nclass)],
              'AGF(Adjusted F-score)' : [(deref(self.thisptr).AGF.get())[i] for i in range(self.Nclass)],
              'OC(Overlap coefficient)' : [(deref(self.thisptr).OC.get())[i] for i in range(self.Nclass)],
              'OOC(Otsuka-Ochiai coefficient)' : [(deref(self.thisptr).OOC.get())[i] for i in range(self.Nclass)],
              'AUPR(Area under the PR curve)' : [(deref(self.thisptr).AUPR.get())[i] for i in range(self.Nclass)],
              'BCD(Bray-Curtis dissimilarity)' : [(deref(self.thisptr).BCD.get())[i] for i in range(self.Nclass)],
              'Overall ACC' : deref(self.thisptr).overall_accuracy,
              'Overall RACCU' : deref(self.thisptr).overall_random_accuracy_unbiased,
              'Overall RACC' : deref(self.thisptr).overall_random_accuracy,
              'Kappa' : deref(self.thisptr).overall_kappa,
              'Scott PI' : deref(self.thisptr).PI,
              'Get AC1' : deref(self.thisptr).AC1,
              'Bennett S' : deref(self.thisptr).S,
              'Kappa Standard Error' : deref(self.thisptr).kappa_SE,
              'Kappa Unbiased' : deref(self.thisptr).kappa_unbiased,
              'Kappa No Prevalence' : deref(self.thisptr).kappa_no_prevalence,
              'Kappa 95% CI': (deref(self.thisptr).kappa_CI_up, deref(self.thisptr).kappa_CI_down),
              'Standard Error' : deref(self.thisptr).overall_accuracy_se,
              '95% CI': (deref(self.thisptr).overall_accuracy_ci_up, deref(self.thisptr).overall_accuracy_ci_down),
              'Chi-Squared' : deref(self.thisptr).chi_square,
              'Phi-Squared' : deref(self.thisptr).phi_square,
              'Cramer V' : deref(self.thisptr).cramer_V,
              'Response Entropy' : deref(self.thisptr).response_entropy,
              'Reference Entropy' : deref(self.thisptr).reference_entropy,
              'Cross Entropy' : deref(self.thisptr).cross_entropy,
              'Joint Entropy' : deref(self.thisptr).join_entropy,
              'Conditional Entropy' : deref(self.thisptr).conditional_entropy,
              'Mutual Information' : deref(self.thisptr).mutual_information,
              'KL Divergence' : deref(self.thisptr).kl_divergence,
              'Lambda B' : deref(self.thisptr).lambda_B,
              'Lambda A' : deref(self.thisptr).lambda_A,
              'Chi-Squared DF' : deref(self.thisptr).DF,
              'Overall J': (deref(self.thisptr).overall_jaccard_index, deref(self.thisptr).overall_jaccard_index / self.Nclass),
              'Hamming loss' : deref(self.thisptr).hamming_loss,
              'Zero-one Loss' : deref(self.thisptr).zero_one_loss,
              'NIR' : deref(self.thisptr).NIR,
              'P-value' : deref(self.thisptr).p_value,
              'Overall CEN' : deref(self.thisptr).overall_CEN,
              'Overall MCEN' : deref(self.thisptr).overall_MCEN,
              'Overall MCC' : deref(self.thisptr).overall_MCC,
              'RR' : deref(self.thisptr).RR,
              'CBA' : deref(self.thisptr).CBA,
              'AUNU' : deref(self.thisptr).AUNU,
              'AUNP' : deref(self.thisptr).AUNP,
              'RCI' : deref(self.thisptr).RCI,
              'CSI' : deref(self.thisptr).CSI,
              'Pearson C' : deref(self.thisptr).overall_pearson_C,
              'TPR Micro' : deref(self.thisptr).TPR_PPV_F1_micro,
              'PPV Micro' : deref(self.thisptr).TPR_PPV_F1_micro,
              'F1 Micro' : deref(self.thisptr).TPR_PPV_F1_micro,
              'SOA6(Matthews)' : deref(self.thisptr).MCC_analysis,
              'SOA4(Cicchetti)' : deref(self.thisptr).kappa_analysis_cicchetti,
              'SOA1(Landis & Koch)' : deref(self.thisptr).kappa_analysis_koch,
              'SOA2(Fleiss)' : deref(self.thisptr).kappa_analysis_fleiss,
              'SOA3(Altman)' : deref(self.thisptr).kappa_analysis_altman,
              'SOA5(Cramer)' : deref(self.thisptr).V_analysis,
              'TPR Macro' : deref(self.thisptr).TPR_macro,
              'PPV Macro' : deref(self.thisptr).PPV_macro,
              'ACC Macro' : deref(self.thisptr).ACC_macro,
              'F1 Macro' : deref(self.thisptr).F1_macro,
            }

    _mcc_analysis = ['Negligible', 'Weak', 'Moderate', 'Strong', 'Very Strong', 'None']
    _nlr_analysis = ['Good', 'Fair', 'Poor', 'Negligible', 'None']
    _plr_analysis = ['Negligible', 'Poor', 'Fair', 'Good', 'None']
    _dp_analysis  = ['Poor', 'Limited', 'Fair', 'None']
    _auc_analysis = ['Poor', 'Fair', 'Good', 'Very Good', 'Excellent', 'None']
    _V_analysis   = ['Negligible', 'Weak', 'Moderate', 'Relatively Strong', 'Strong', 'Very Strong', 'None']
    _kcicchetti_analysis = ['Poor', 'Fair', 'Good', 'Excellent', 'None']
    _kkoch_analysis      = ['Poor', 'Slight', 'Fair', 'Moderate', 'Substantial', 'Almost Perfect', 'None']
    _kfleiss_analysis    = ['Poor', 'Intermediate to Good', 'Excellent', 'None']
    _kaltman_analysis    = ['Poor', 'Fair', 'Moderate', 'Good', 'Very Good', 'None']

    score['SOA1(Landis & Koch)'] = _kkoch_analysis[     int(score['SOA1(Landis & Koch)'])]
    score['SOA2(Fleiss)'       ] = _kfleiss_analysis[   int(score['SOA2(Fleiss)'])]
    score['SOA3(Altman)'       ] = _kaltman_analysis[   int(score['SOA3(Altman)'])]
    score['SOA4(Cicchetti)'    ] = _kcicchetti_analysis[int(score['SOA4(Cicchetti)'])]
    score['SOA5(Cramer)'       ] = _V_analysis[         int(score['SOA5(Cramer)'])]
    score['SOA6(Matthews)'     ] = _mcc_analysis[       int(score['SOA6(Matthews)'])]

    score['NLRI(Negative likelihood ratio interpretation)'] = [_nlr_analysis[int(item)] for item in score['NLRI(Negative likelihood ratio interpretation)']]
    score['PLRI(Positive likelihood ratio interpretation)'] = [_plr_analysis[int(item)] for item in score['PLRI(Positive likelihood ratio interpretation)']]
    score['AUCI(AUC value interpretation)'] = [_auc_analysis[int(item)] for item in score['AUCI(AUC value interpretation)']]
    score['DPI(Discriminant power interpretation)' ] = [_dp_analysis[int(item)] for item in score['DPI(Discriminant power interpretation)' ]]
    score['MCCI(Matthews correlation coefficient interpretation)'] = [_mcc_analysis[int(item)] for item in score['MCCI(Matthews correlation coefficient interpretation)']]

    return score

  @property
  def get_available_metrics (self):
    return {
             'confusion_matrix' : 'Confusion Matrix',
             'class_true_positive' : 'TP(True positive/hit)',
             'class_false_negative' : 'FN(False negative/miss/type 2 error)',
             'class_false_positive' : 'FP(False positive/type 1 error/false alarm)',
             'class_true_negative' : 'TN(True negative/correct rejection)',
             'class_conditional_positive' : 'P(Condition positive or support)',
             'class_conditional_negative' : 'N(Condition negative)',
             'class_test_outcome_positive' : 'TOP(Test outcome positive)',
             'class_test_outcome_negative' : 'TON(Test outcome negative)',
             'class_true_positive_rate' : 'TPR(Sensitivity / recall / hit rate / true positive rate)',
             'class_true_negative_rate' : 'TNR(Specificity or true negative rate)',
             'class_precision' : 'PPV(Precision or positive predictive value)',
             'class_negative_predictions' : 'NPV(Negative predictive value)',
             'class_false_negative_rate' : 'FNR(Miss rate or false negative rate)',
             'class_false_positive_rate' : 'FPR(Fall-out or false positive rate)',
             'class_false_discovery_rate' : 'FDR(False discovery rate)',
             'class_false_omission_rate' : 'FOR(False omission rate)',
             'class_accuracy' : 'ACC(Accuracy)',
             'class_f1score' : 'F1(F1 score - harmonic mean of precision and sensitivity)',
             'class_f05score' : 'F0.5(F0.5 score)',
             'class_f2score' : 'F2(F2 score)',
             'class_matthews_correlation_coefficient' : 'MCC(Matthews correlation coefficient)',
             'class_informedness' : 'BM(Informedness or bookmaker informedness)',
             'class_markedness' : 'MK(Markedness)',
             'class_positive_likelihood_ratio' : 'PLR(Positive likelihood ratio)',
             'class_negative_likelihood_ratio' : 'NLR(Negative likelihood ratio)',
             'class_diagnostic_ratio' : 'DOR(Diagnostic odds ratio)',
             'class_prevalence' : 'PRE(Prevalence)',
             'class_sensitivity' : 'G(G-measure geometric mean of precision and sensitivity)',
             'class_random_accuracy' : 'RACC(Random accuracy)',
             'class_error_rate' : 'ERR(Error rate)',
             'class_random_accuracy_unbiased' : 'RACCU(Random accuracy unbiased)',
             'class_jaccard_score' : 'J(Jaccard index)',
             'class_information_score' : 'IS(Information score)',
             'class_confusion_entropy' : 'CEN(Confusion entropy)',
             'class_modified_confusion_entropy' : 'MCEN(Modified confusion entropy)',
             'class_auc_score' : 'AUC(Area Under the ROC curve)',
             'class_distance_index' : 'dInd(Distance index)',
             'class_similarity_index' : 'sInd(Similarity index)',
             'class_discriminant_power' : 'DP(Discriminant power)',
             'class_youden_index' : 'Y(Youden index)',
             'class_gini_index' : 'GI(Gini index)',
             'class_lift_score' : 'LS(Lift score)',
             'class_am_score' : 'AM(Difference between automatic and manual classification)',
             'class_optimized_precision' : 'OP(Optimized precision)',
             'class_balanced_accuracy_index' : 'IBA(Index of balanced accuracy)',
             'class_geometric_mean' : 'GM(G-mean geometric mean of specificity and sensitivity)',
             'class_colligation_coefficient' : 'Q(Yule Q - coefficient of colligation)',
             'class_adjusted_geometric_mean' : 'AGM(Adjusted geometric mean)',
             'class_adjusted_fscore' : 'AGF(Adjusted F-score)',
             'class_overlap' : 'OC(Overlap coefficient)',
             'class_otsuka_coefficient' : 'OOC(Otsuka-Ochiai coefficient)',
             'class_aupr_score' : 'AUPR(Area under the PR curve)',
             'class_curtis_dissimilarity' : 'BCD(Bray-Curtis dissimilarity)',
             'accuracy_score' : 'Overall ACC',
             'random_accuracy_unbiased' : 'Overall RACCU',
             'random_accuracy' : 'Overall RACC',
             'cohen_kappa_score' : 'Kappa',
             'one_over_classes' : 'PC_S',
             'scott_pi_score' : 'Scott PI',
             'gwet_score' : 'Gwet AC1',
             'bennet_score' : 'Bennett S',
             'cohen_kappa_standard_score' : 'Kappa Standard',
             'cohen_kappa_unbiased_score' : 'Kappa Unbiased',
             'cohen_kappa_no_prevalence_score' : 'Kappa No',
             'cohen_kappa_95CI_score' : 'Kappa 95',
             'standard_error' : 'Standard Error',
             '95_confidence_level' : '95% CI',
             'chi2' : 'Chi-Squared',
             'phi2' : 'Phi-Squared',
             'cramer_score' : 'Cramer V',
             'response_entropy_score' : 'Response Entropy',
             'reference_entropy_score' : 'Reference Entropy',
             'cross_entropy_score' : 'Cross Entropy',
             'joint_entropy_score' : 'Joint Entropy',
             'conditional_entropy_score' : 'Conditional Entropy',
             'mutual_info_score' : 'Mutual Information',
             'kl_divergence_score' : 'KL Divergence',
             'goodman_lambda_b' : 'Lambda B',
             'goodman_lambda_a' : 'Lambda A',
             'chi2' : 'Chi-Squared',
             'jaccard_score' : 'Overall J',
             'hamming_loss' : 'Hamming loss',
             'zero_one_loss' : 'Zero-one Loss',
             'no_informative_rate' : 'NIR',
             'p_value' : 'P-value',
             'confusion_entropy' : 'Overall CEN',
             'modified_confusion_entropy' : 'Overall MCEN',
             'matthews_corrcoef' : 'Overall MCC',
             'global_performance_index' : 'RR',
             'class_balanced_accuracy' : 'CBA',
             'aunu_score' : 'AUNU',
             'aunp_score' : 'AUNP',
             'relative_classifier_info' : 'RCI',
             'pearson_c' : 'Pearson C',
             'f1_micro' : 'F1 Micro',
             'precision_micro' : 'PPV Micro',
             'recall_micro' : 'TPR Micro',
             'accuracy_macro' : 'ACC Macro',
             'f1_macro' : 'F1 Macro',
             'recall_macro' : 'TPR Macro',
             'precision_macro' : 'PPV Macro',
             'classification_sucess_index' : 'CSI',
           }

  @property
  def num_classes (self):
    return deref(self.thisptr).classes.size()

  def __repr__ (self):
    return '<Scorer (classes: {0})>'.format(self.num_classes)
  