# distutils: language = c++
# cython: language_level=2

from cython.operator cimport dereference as deref
from libcpp.memory cimport unique_ptr

from Scorer cimport scorer

cdef class _scorer:

  cdef unique_ptr[scorer] thisptr

  cdef public:
    int Nclass

  def __init__ (self):
    self.thisptr.reset(new scorer())


  def evaluate (self, int[::1] lbl_true, int[::1] lbl_pred, int n_lbl):
    deref(self.thisptr).compute_score(&lbl_true[0], &lbl_pred[0], n_lbl, n_lbl)

    self.Nclass = deref(self.thisptr).classes.size()

    score = {
              'classes'          : deref(self.thisptr).classes,

              'confusion_matrix' : [(deref(self.thisptr).confusion_matrix.get())[i] for i in range(self.Nclass * self.Nclass)],
              'TP' :               [(deref(self.thisptr).TP.get())[i] for i in range(self.Nclass)],
              'FN' :               [(deref(self.thisptr).FN.get())[i] for i in range(self.Nclass)],
              'FP' :               [(deref(self.thisptr).FP.get())[i] for i in range(self.Nclass)],
              'TN' :               [(deref(self.thisptr).TN.get())[i] for i in range(self.Nclass)],
              'POP' :              [(deref(self.thisptr).POP.get())[i] for i in range(self.Nclass)],
              'P' :                [(deref(self.thisptr).P.get())[i] for i in range(self.Nclass)],
              'N' :                [(deref(self.thisptr).N.get())[i] for i in range(self.Nclass)],
              'TOP' :              [(deref(self.thisptr).TOP.get())[i] for i in range(self.Nclass)],
              'TON' :              [(deref(self.thisptr).TON.get())[i] for i in range(self.Nclass)],
              'TPR' :              [(deref(self.thisptr).TPR.get())[i] for i in range(self.Nclass)],
              'TNR' :              [(deref(self.thisptr).TNR.get())[i] for i in range(self.Nclass)],
              'PPV' :              [(deref(self.thisptr).PPV.get())[i] for i in range(self.Nclass)],
              'NPV' :              [(deref(self.thisptr).NPV.get())[i] for i in range(self.Nclass)],
              'FNR' :              [(deref(self.thisptr).FNR.get())[i] for i in range(self.Nclass)],
              'FPR' :              [(deref(self.thisptr).FPR.get())[i] for i in range(self.Nclass)],
              'FDR' :              [(deref(self.thisptr).FDR.get())[i] for i in range(self.Nclass)],
              'FOR' :              [(deref(self.thisptr).FOR.get())[i] for i in range(self.Nclass)],
              'ACC' :              [(deref(self.thisptr).ACC.get())[i] for i in range(self.Nclass)],
              'F1_SCORE' :         [(deref(self.thisptr).F1_SCORE.get())[i] for i in range(self.Nclass)],
              'F05_SCORE' :        [(deref(self.thisptr).F05_SCORE.get())[i] for i in range(self.Nclass)],
              'F2_SCORE' :         [(deref(self.thisptr).F2_SCORE.get())[i] for i in range(self.Nclass)],
              'MCC' :              [(deref(self.thisptr).MCC.get())[i] for i in range(self.Nclass)],
              'BM' :               [(deref(self.thisptr).BM.get())[i] for i in range(self.Nclass)],
              'MK' :               [(deref(self.thisptr).MK.get())[i] for i in range(self.Nclass)],
              'PLR' :              [(deref(self.thisptr).PLR.get())[i] for i in range(self.Nclass)],
              'NLR' :              [(deref(self.thisptr).NLR.get())[i] for i in range(self.Nclass)],
              'DOR' :              [(deref(self.thisptr).DOR.get())[i] for i in range(self.Nclass)],
              'PRE' :              [(deref(self.thisptr).PRE.get())[i] for i in range(self.Nclass)],
              'G' :                [(deref(self.thisptr).G.get())[i] for i in range(self.Nclass)],
              'RACC' :             [(deref(self.thisptr).RACC.get())[i] for i in range(self.Nclass)],
              'ERR_ACC' :          [(deref(self.thisptr).ERR_ACC.get())[i] for i in range(self.Nclass)],
              'RACCU' :            [(deref(self.thisptr).RACCU.get())[i] for i in range(self.Nclass)],
              'jaccard_index' :    [(deref(self.thisptr).jaccard_index.get())[i] for i in range(self.Nclass)],
              'IS' :               [(deref(self.thisptr).IS.get())[i] for i in range(self.Nclass)],
              'CEN' :              [(deref(self.thisptr).CEN.get())[i] for i in range(self.Nclass)],
              'MCEN' :             [(deref(self.thisptr).MCEN.get())[i] for i in range(self.Nclass)],
              'AUC' :              [(deref(self.thisptr).AUC.get())[i] for i in range(self.Nclass)],
              'dIND' :             [(deref(self.thisptr).dIND.get())[i] for i in range(self.Nclass)],
              'sIND' :             [(deref(self.thisptr).sIND.get())[i] for i in range(self.Nclass)],
              'DP' :               [(deref(self.thisptr).DP.get())[i] for i in range(self.Nclass)],
              'Y' :                [(deref(self.thisptr).Y.get())[i] for i in range(self.Nclass)],
              'PLRI' :             [(deref(self.thisptr).PLRI.get())[i] for i in range(self.Nclass)],
              'NLRI' :             [(deref(self.thisptr).NLRI.get())[i] for i in range(self.Nclass)],
              'DPI' :              [(deref(self.thisptr).DPI.get())[i] for i in range(self.Nclass)],
              'AUCI' :             [(deref(self.thisptr).AUCI.get())[i] for i in range(self.Nclass)],
              'GI' :               [(deref(self.thisptr).GI.get())[i] for i in range(self.Nclass)],
              'LS' :               [(deref(self.thisptr).LS.get())[i] for i in range(self.Nclass)],
              'AM' :               [(deref(self.thisptr).AM.get())[i] for i in range(self.Nclass)],
              'OP' :               [(deref(self.thisptr).OP.get())[i] for i in range(self.Nclass)],
              'IBA' :              [(deref(self.thisptr).IBA.get())[i] for i in range(self.Nclass)],
              'GM' :               [(deref(self.thisptr).GM.get())[i] for i in range(self.Nclass)],
              'Q' :                [(deref(self.thisptr).Q.get())[i] for i in range(self.Nclass)],
              'AGM' :              [(deref(self.thisptr).AGM.get())[i] for i in range(self.Nclass)],
              'MCCI' :             [(deref(self.thisptr).MCCI.get())[i] for i in range(self.Nclass)],
              'AGF' :              [(deref(self.thisptr).AGF.get())[i] for i in range(self.Nclass)],
              'OC' :               [(deref(self.thisptr).OC.get())[i] for i in range(self.Nclass)],
              'OOC' :              [(deref(self.thisptr).OOC.get())[i] for i in range(self.Nclass)],
              'AUPR' :             [(deref(self.thisptr).AUPR.get())[i] for i in range(self.Nclass)],
              'BCD' :              [(deref(self.thisptr).BCD.get())[i] for i in range(self.Nclass)],

              'overall_accuracy' :                 deref(self.thisptr).overall_accuracy,
              'overall_random_accuracy_unbiased' : deref(self.thisptr).overall_random_accuracy_unbiased,
              'overall_random_accuracy' :          deref(self.thisptr).overall_random_accuracy,
              'overall_kappa' :                    deref(self.thisptr).overall_kappa,
              'PC_PI' :                            deref(self.thisptr).PC_PI,
              'PC_AC1' :                           deref(self.thisptr).PC_AC1,
              'PC_S' :                             deref(self.thisptr).PC_S,
              'PI' :                               deref(self.thisptr).PI,
              'AC1' :                              deref(self.thisptr).AC1,
              'S' :                                deref(self.thisptr).S,
              'kappa_SE' :                         deref(self.thisptr).kappa_SE,
              'kappa_unbiased' :                   deref(self.thisptr).kappa_unbiased,
              'kappa_no_prevalence' :              deref(self.thisptr).kappa_no_prevalence,
              'kappa_CI' :                         deref(self.thisptr).kappa_CI,
              'overall_accuracy_se' :              deref(self.thisptr).overall_accuracy_se,
              'overall_accuracy_ci' :              deref(self.thisptr).overall_accuracy_ci,
              'chi_square' :                       deref(self.thisptr).chi_square,
              'phi_square' :                       deref(self.thisptr).phi_square,
              'cramers_V_calc' :                   deref(self.thisptr).cramers_V_calc,
              'response_entropy' :                 deref(self.thisptr).response_entropy,
              'reference_entropy' :                deref(self.thisptr).reference_entropy,
              'cross_entropy' :                    deref(self.thisptr).cross_entropy,
              'join_entropy' :                     deref(self.thisptr).join_entropy,
              'conditional_entropy' :              deref(self.thisptr).conditional_entropy,
              'mutual_information' :               deref(self.thisptr).mutual_information,
              'kl_divergence' :                    deref(self.thisptr).kl_divergence,
              'lambda_B' :                         deref(self.thisptr).lambda_B,
              'lambda_A' :                         deref(self.thisptr).lambda_A,
              'DF' :                               deref(self.thisptr).DF,
              'overall_jaccard_index' :            deref(self.thisptr).overall_jaccard_index,
              'hamming_loss' :                     deref(self.thisptr).hamming_loss,
              'zero_one_loss' :                    deref(self.thisptr).zero_one_loss,
              'NIR' :                              deref(self.thisptr).NIR,
              'p_value' :                          deref(self.thisptr).p_value,
              'overall_CEN' :                      deref(self.thisptr).overall_CEN,
              'overall_MCEN' :                     deref(self.thisptr).overall_MCEN,
              'overall_MCC' :                      deref(self.thisptr).overall_MCC,
              'RR' :                               deref(self.thisptr).RR,
              'CBA' :                              deref(self.thisptr).CBA,
              'AUNU' :                             deref(self.thisptr).AUNU,
              'AUNP' :                             deref(self.thisptr).AUNP,
              'RCI' :                              deref(self.thisptr).RCI,
              'overall_pearson_C' :                deref(self.thisptr).overall_pearson_C,
              'TPR_PPV_F1_micro' :                 deref(self.thisptr).TPR_PPV_F1_micro
            }

    return score


  @property
  def num_classes (self):
    return deref(self.thisptr).classes.size()

  def __repr__ (self):
    return '<Scorer (classes: {})>'.format(self.num_classes)
