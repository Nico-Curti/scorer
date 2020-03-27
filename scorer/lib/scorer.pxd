# distutils: language = c++
# cython: language_level=2

from libcpp.vector cimport vector
from libcpp.memory cimport unique_ptr

cdef extern from "scorer.h":

  cppclass scorer:

    scorer() except +

    # Attributes

    vector[float] classes

    unique_ptr[float] confusion_matrix
    unique_ptr[float] TP
    unique_ptr[float] FN
    unique_ptr[float] FP
    unique_ptr[float] TN
    unique_ptr[float] POP
    unique_ptr[float] P
    unique_ptr[float] N
    unique_ptr[float] TOP
    unique_ptr[float] TON
    unique_ptr[float] TPR
    unique_ptr[float] TNR
    unique_ptr[float] PPV
    unique_ptr[float] NPV
    unique_ptr[float] FNR
    unique_ptr[float] FPR
    unique_ptr[float] FDR
    unique_ptr[float] FOR
    unique_ptr[float] ACC
    unique_ptr[float] F1_SCORE
    unique_ptr[float] F05_SCORE
    unique_ptr[float] F2_SCORE
    unique_ptr[float] MCC
    unique_ptr[float] BM
    unique_ptr[float] MK
    unique_ptr[float] PLR
    unique_ptr[float] NLR
    unique_ptr[float] DOR
    unique_ptr[float] PRE
    unique_ptr[float] G
    unique_ptr[float] RACC
    unique_ptr[float] ERR_ACC
    unique_ptr[float] RACCU
    unique_ptr[float] jaccard_index
    unique_ptr[float] IS
    unique_ptr[float] CEN
    unique_ptr[float] MCEN
    unique_ptr[float] AUC
    unique_ptr[float] dIND
    unique_ptr[float] sIND
    unique_ptr[float] DP
    unique_ptr[float] Y
    unique_ptr[float] PLRI
    unique_ptr[float] NLRI
    unique_ptr[float] DPI
    unique_ptr[float] AUCI
    unique_ptr[float] GI
    unique_ptr[float] LS
    unique_ptr[float] AM
    unique_ptr[float] OP
    unique_ptr[float] IBA
    unique_ptr[float] GM
    unique_ptr[float] Q
    unique_ptr[float] AGM
    unique_ptr[float] MCCI
    unique_ptr[float] AGF
    unique_ptr[float] OC
    unique_ptr[float] OOC
    unique_ptr[float] AUPR
    unique_ptr[float] BCD
    unique_ptr[float] ICSI

    float overall_accuracy
    float overall_random_accuracy_unbiased
    float overall_random_accuracy
    float overall_kappa
    float PC_PI
    float PC_AC1
    float PC_S
    float PI
    float AC1
    float S
    float kappa_SE
    float kappa_unbiased
    float kappa_no_prevalence
    float kappa_CI_up
    float kappa_CI_down
    float overall_accuracy_se
    float overall_accuracy_ci_up
    float overall_accuracy_ci_down
    float chi_square
    float phi_square
    float cramers_V_calc
    float response_entropy
    float reference_entropy
    float cross_entropy
    float join_entropy
    float conditional_entropy
    float mutual_information
    float kl_divergence
    float lambda_B
    float lambda_A
    float DF
    float overall_jaccard_index
    float hamming_loss
    float zero_one_loss
    float NIR
    float p_value
    float overall_CEN
    float overall_MCEN
    float overall_MCC
    float RR
    float CBA
    float AUNU
    float AUNP
    float RCI
    float overall_pearson_C
    float TPR_PPV_F1_micro
    float CSI;
    float cramer_V
    float MCC_analysis
    float kappa_analysis_cicchetti
    float kappa_analysis_koch
    float kappa_analysis_fleiss
    float kappa_analysis_altman
    float V_analysis
    float TPR_macro
    float PPV_macro
    float ACC_macro
    float F1_macro

    # Methods
    void compute_score(int *, int *, int, int)
    void print_class_stats[T](T&)
    void print_overall_stats[T](T&)


cdef extern from "<utility>" namespace "std" nogil:

  cdef unique_ptr[scorer] move(unique_ptr[scorer])


cdef class _scorer:

  cdef unique_ptr[scorer] thisptr

  cdef public:
    int Nclass
