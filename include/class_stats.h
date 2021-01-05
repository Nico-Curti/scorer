#ifndef __class_stats_h__
#define __class_stats_h__

#include <common_stats.h>

/**
* @brief Number of positive outcomes.
*
* @details
* ```python
* TOP = TP + FP
* ```
*
* @param TP array of true positives
* @param FP array of false positives
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of the number of positives outcomes for each class.
*/
struct // TOP(Test outcome positive)
{
  auto operator() (const float * TP, const float * FP, const int & Nclass)
  {
    std :: unique_ptr < float[] > TOP (new float[Nclass]);
    std :: transform(TP, TP + Nclass, FP, TOP.get(), [](const float & tp, const float & fp){return tp + fp;});
    return TOP;
  }
} get_TOP;

/**
* @brief Number of negative outcomes.
*
* @details
* ```python
* TON = TN + FN
* ```
*
* @param TN array of true negatives
* @param FN array of false negative
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of the number of negative outcomes for each class.
*/
struct // TON(Test outcome negative)
{
  auto operator() (const float * TN, const float * FN, const int & Nclass)
  {
    std :: unique_ptr < float[] > TON (new float[Nclass]);
    std :: transform(TN, TN + Nclass, FN, TON.get(), [](const float & tn, const float & fn){return tn + fn;});
    return TON;
  }
} get_TON;

/**
* @brief True positive rates
*
* @details Sensitivity (also called the true positive rate, the recall, or
* probability of detection in some fields) measures the proportion of positives
* that are correctly identified as such (e.g. the percentage of sick people who
* are correctly identified as having the condition)
*
* ```python
* TPR = TP / P = TP / (TP + FN)
* ```
*
* @param TP array of true positives
* @param FN array of false negative
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of the true positive rate outcomes for each class.
*/
struct // TPR(Sensitivity / recall / hit rate / true positive rate)
{
  auto operator() (const float * TP, const float * FN, const int & Nclass)
  {
    std :: unique_ptr < float[] > TPR (new float[Nclass]);
    std :: transform(TP, TP + Nclass, FN, TPR.get(), [](const float & i1, const float & i2){return i1 / (i1 + i2 + epsil);});
    return TPR;
  }
} get_TPR;

/**
* @brief True negative rates
*
* @details Specificity (also called the true negative rate) measures the
* proportion of negatives that are correctly identified as such
* (e.g. the percentage of healthy people who are correctly identified as not
* having the condition)
*
* ```python
* TPN = TN / N = TN / (TN + FP)
* ```
*
* @param TN array of true negatives
* @param FP array of false positives
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of the true negative rate outcomes for each class.
*/
struct // TNR(Specificity or true negative rate)
{
  auto operator() (const float * TN, const float * FP, const int & Nclass)
  {
    std :: unique_ptr < float[] > TNR (new float[Nclass]);
    std :: transform(TN, TN + Nclass, FP, TNR.get(), [](const float & i1, const float & i2){return i1 / (i1 + i2 + epsil);});
    return TNR;
  }
} get_TNR;

/**
* @brief Positive predictive value
*
* @details Positive predictive value (PPV) is the proportion of positives that
* correspond to the presence of the condition
*
* ```python
* PPV = TP / (TP + FP)
* ```
*
* @param TP array of true positives
* @param FP array of false positives
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of the positive predicted values for each class.
*/
struct // PPV(Precision or positive predictive value)
{
  auto operator() (const float * TP, const float * FP, const int & Nclass)
  {
    std :: unique_ptr < float[] > PPV (new float[Nclass]);
    std :: transform(TP, TP + Nclass, FP, PPV.get(), [](const float & i1, const float & i2){return i1 / (i1 + i2 + epsil);});
    return PPV;
  }
} get_PPV;

/**
* @brief Negative predictive value
*
* @details Negative predictive value (NPV) is the proportion of negatives that
* correspond to the absence of the condition
*
* ```python
* NPV = TN / (TN + FN)
* ```
*
* @param TP array of true negatives
* @param FP array of false negatives
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of the negative predicted values for each class.
*/
struct // NPV(Negative predictive value)
{
  auto operator() (const float * TN, const float * FN, const int & Nclass)
  {
    std :: unique_ptr < float[] > NPV (new float[Nclass]);
    std :: transform(TN, TN + Nclass, FN, NPV.get(), [](const float & i1, const float & i2){return i1 / (i1 + i2 + epsil);});
    return NPV;
  }
} get_NPV;

/**
* @brief False negative rate
*
* @details The false negative rate is the proportion of positives which yield
* negative test outcomes with the test, i.e., the conditional probability of a
* negative test result given that the condition being looked for is present.
*
* ```python
* FNR = FN / P = FN / (FN + TP) = 1 - TPR
* ```
*
* @param TPR array of true positive rates
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of the false negative rates for each class.
*/
struct // FNR(Miss rate or false negative rate)
{
  auto operator() (const float * TPR, const int & Nclass)
  {
    std :: unique_ptr < float[] > FNR (new float[Nclass]);
    std :: transform(TPR, TPR + Nclass, FNR.get(), [](const float & item){return 1.f - item;});
    return FNR;
  }
} get_FNR;

/**
* @brief False positive rate
*
* @details The false positive rate is the proportion of all negatives that still
* yield positive test outcomes, i.e., the conditional probability of a positive test
* result given an event that was not present.
* The false positive rate is equal to the significance level.
* The specificity of the test is equal to  1 minus the false positive rate.
*
* ```python
* FPR = FP / N = FP / (FP + TN) = 1 - TNR
* ```
*
* @param TNR array of true negative rates
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of the false positive rates for each class.
*/
struct // FPR(Fall-out or false positive rate)
{
  auto operator() (const float * TNR, const int & Nclass)
  {
    std :: unique_ptr < float[] > FPR (new float[Nclass]);
    std :: transform(TNR, TNR + Nclass, FPR.get(), [](const float & item){return 1.f - item;});
    return FPR;
  }
} get_FPR;

/**
* @brief False discovery rate
*
* @details The false discovery rate (FDR) is a method of conceptualizing the
* rate of type I errors in null hypothesis testing when conducting multiple
* comparisons.
* FDR-controlling procedures are designed to control the expected proportion of
* "discoveries" (rejected null hypotheses) that are false (incorrect rejections).
*
* ```python
* FDR = FP / (FP + TP) = 1 - PPV
* ```
*
* @param PPV array of positive predictive values
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of the false discovery rates for each class.
*/
struct // FDR(False discovery rate)
{
  auto operator() (const float * PPV, const int & Nclass)
  {
    std :: unique_ptr < float[] > FDR (new float[Nclass]);
    std :: transform(PPV, PPV + Nclass, FDR.get(), [](const float & item){return 1.f - item;});
    return FDR;
  }
} get_FDR;

/**
* @brief False omission rate
*
* @details False omission rate (FOR) is a statistical method used in
* multiple hypothesis testing to correct for multiple comparisons and it
* is the complement of the negative predictive value.
* It measures the proportion of false negatives which are incorrectly rejected.
*
* ```python
* FOR = FN / (FN + TN) = 1 - NPV
* ```
*
* @param NPV array of negative predictive values
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of the false omission rates for each class.
*/
struct // FOR(False omission rate)
{
  auto operator() (const float * NPV, const int & Nclass)
  {
    std :: unique_ptr < float[] > FOR (new float[Nclass]);
    std :: transform(NPV, NPV + Nclass, FOR.get(), [](const float & item){return 1.f - item;});
    return FOR;
  }
} get_FOR;

/**
* @brief Accuracy
*
* @details The accuracy is the number of correct predictions from
* all predictions made.
*
* ```python
* ACC = (TP + TN) / (P + N) = (TP + TN) / (TP + TN + FP + FN)
* ```
*
* @param TP array of true positives
* @param FP array of false positives
* @param FN array of false negative
* @param TN array of true negatives
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of accuracies for each class.
*/
struct // ACC(Accuracy)
{
  auto operator() (const float * TP, const float * FP, const float * FN, const float * TN, const int & Nclass)
  {
    std :: unique_ptr < float[] > ACC (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      ACC[i] = ( TP[i] + TN[i] ) / (TP[i] + TN[i] + FN[i] + FP[i] + epsil);
    return ACC;
  }
} get_ACC;

/**
* @brief Fbeta-score
*
* @details In statistical analysis of classification, the F1 score
* (also F-score or F-measure) is a measure of a test's accuracy.
* It considers both the precision p and the recall r of the test to
* compute the score.
* The F1 score is the harmonic average of the precision and recall,
* where F1 score reaches its best value at 1 (perfect precision and recall)
* and worst at 0.
* In this case the score is evaluated with beta=1.
*
* ```python
* Fbeta = (1 + beta**2) * (PPV * TPR) / (beta**2 * PPV) + TPR = (1 + beta**2) * TP / ((1 + beta**2) * TP + FP + beta**2 * FN)
* ```
*
* @param TP array of true positives
* @param FP array of false positives
* @param FN array of false negative
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of F1 scores for each class.
*/
struct // F1(F1 score - harmonic mean of precision and sensitivity)
{
  auto operator() (const float * TP, const float * FP, const float * FN, const int & Nclass)
  {
    std :: unique_ptr < float[] > F1_SCORE (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      F1_SCORE[i] = (2.f * TP[i]) / (2.f * TP[i] + FP[i] + FN[i] + epsil);
    return F1_SCORE;
  }
} get_F1_SCORE;

/**
* @brief Fbeta-score
*
* @details In statistical analysis of classification, the F1 score
* (also F-score or F-measure) is a measure of a test's accuracy.
* It considers both the precision p and the recall r of the test to
* compute the score.
* The F1 score is the harmonic average of the precision and recall,
* where F1 score reaches its best value at 1 (perfect precision and recall)
* and worst at 0.
* In this case the score is evaluated with beta=0.5.
*
* ```python
* Fbeta = (1 + beta**2) * (PPV * TPR) / (beta**2 * PPV) + TPR = (1 + beta**2) * TP / ((1 + beta**2) * TP + FP + beta**2 * FN)
* ```
*
* @param TP array of true positives
* @param FP array of false positives
* @param FN array of false negative
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of F1 scores for each class.
*/
struct // F0.5(F0.5 score)
{
  auto operator() (const float * TP, const float * FP, const float * FN, const int & Nclass)
  {
    std :: unique_ptr < float[] > F05_SCORE (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      F05_SCORE[i] = (1.25f * TP[i]) / (1.25f * TP[i] + FP[i] + .25f * FN[i] + epsil);
    return F05_SCORE;
  }
} get_F05_SCORE;

/**
* @brief Fbeta-score
*
* @details In statistical analysis of classification, the F1 score
* (also F-score or F-measure) is a measure of a test's accuracy.
* It considers both the precision p and the recall r of the test to
* compute the score.
* The F1 score is the harmonic average of the precision and recall,
* where F1 score reaches its best value at 1 (perfect precision and recall)
* and worst at 0.
* In this case the score is evaluated with beta=2.
*
* ```python
* Fbeta = (1 + beta**2) * (PPV * TPR) / (beta**2 * PPV) + TPR = (1 + beta**2) * TP / ((1 + beta**2) * TP + FP + beta**2 * FN)
* ```
*
* @param TP array of true positives
* @param FP array of false positives
* @param FN array of false negative
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of F1 scores for each class.
*/
struct // F2(F2 score)
{
  auto operator() (const float * TP, const float * FP, const float * FN, const int & Nclass)
  {
    std :: unique_ptr < float[] > F2_SCORE (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      F2_SCORE[i] = (5.f * TP[i]) / (5.f * TP[i] + FP[i] + 4.f * FN[i] + epsil);
    return F2_SCORE;
  }
} get_F2_SCORE;

/**
* @brief Matthews correlation coefficient
*
* @details The Matthews correlation coefficient is used in machine learning as
* a measure of the quality of binary (two-class) classifications, introduced
* by biochemist Brian W. Matthews in 1975.
* It takes into account true and false positives and negatives and is generally
* regarded as a balanced measure that can be used even if the classes are of very
* different sizes. The MCC is, in essence, a correlation coefficient between the
* observed and predicted binary classifications; it returns a value between −1 and +1.
* A coefficient of +1 represents a perfect prediction, 0 no better than random
* prediction and −1 indicates total disagreement between prediction and observation.
*
* ```python
* MCC = (TP * TN - FP * FN) / sqrt((TP + FP) * (TP + FN) * (TN + FP) * (TN + FN))
* ```
*
* @param TP array of true positives
* @param TN array of true negatives
* @param FP array of false positives
* @param FN array of false negative
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of MCC scores for each class.
*/
struct // MCC(Matthews correlation coefficient)
{
  auto operator() (const float * TP, const float * TN, const float * FP, const float * FN, const int & Nclass)
  {
    std :: unique_ptr < float[] > MCC (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      MCC[i] = (TP[i] * TN[i] - FP[i] * FN[i]) / (std :: sqrt( (TP[i] + FP[i]) * (TP[i] + FN[i]) * (TN[i] + FP[i]) * (TN[i] + FN[i]) ) + epsil);
    return MCC;
  }
} get_MCC;

/**
* @brief Bookmaker informedness
*
* @details The informedness of a prediction method as captured by a contingency
* matrix is defined as the probability that the prediction method will make a
* correct decision as opposed to guessing and is calculated using the bookmaker
* algorithm. It is equal to Youden Index.
*
* ```python
* BM = TPR + TNR - 1
* ```
*
* @param TPR array of true positive rates
* @param TNR array of true negative rates
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of BM scores for each class.
*/
struct // BM(Informedness or bookmaker informedness)
{
  auto operator() (const float * TPR, const float * TNR, const int & Nclass)
  {
    std :: unique_ptr < float[] > BM (new float[Nclass]);
    std :: transform(TPR, TPR + Nclass, TNR, BM.get(), [](const float & tp, const float & tn){return tp + tn - 1.f;});
    return BM;
  }
} get_BM;

/**
* @brief Markedness
*
* @details In statistics and psychology, the social science concept of markedness
* is quantified as a measure of how much one variable is marked as a predictor or
* possible cause of another and is also known as △P in simple two-choice cases.
*
* ```python
* MK = PPV + NPV - 1
* ```
*
* @param PPV array of positive predictive values
* @param NPV array of negative predictive values
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of MK scores for each class.
*/
struct // MK(Markedness)
{
  auto operator() (const float * PPV, const float * NPV, const int & Nclass)
  {
    std :: unique_ptr < float[] > MK (new float[Nclass]);
    std :: transform(PPV, PPV + Nclass, NPV, MK.get(), [](const float & tp, const float & tn){return tp + tn - 1.f;});
    return MK;
  }
} get_MK;

/**
* @brief Individual classification success index
*
* @details The Individual Classification Success Index (ICSI), is a
* class-specific symmetric measure defined for classification assessment purpose.
* ICSI is hence 1 minus the sum of type I and type II errors.
* It ranges from −1 (both errors are maximal, i.e. 1) to 1 (both errors are minimal,
* i.e. 0), but the value 0 does not have any clear meaning. The measure is symmetric,
* and linearly related to the arithmetic mean of TPR and PPV
*
* ```python
* ICSI = PPV + TPR - 1
* ```
*
* @param PPV array of positive predictive values
* @param TPR array of true positive rates
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of ICSI for each class.
*/
struct // ICSI(Individual classification success index)
{
  auto operator() (const float * PPV, const float * TPR, const int & Nclass)
  {
    std :: unique_ptr < float[] > ICSI (new float[Nclass]);
    std :: transform(PPV, PPV + Nclass, TPR, ICSI.get(), [](const float & tp, const float & tn){return tp + tn - 1.f;});
    return ICSI;
  }
} get_ICSI;

/**
* @brief Positive likelihood ratio
*
* @details Likelihood ratios are used for assessing the value of performing a
* diagnostic test. They use the sensitivity and specificity of the test to
* determine whether a test result usefully changes the probability that a condition
* (such as a disease state) exists. The first description of the use of likelihood
* ratios for decision rules was made at a symposium on information theory in 1954.
*
* ```python
* PLR = TPR / FPR
* ```
*
* @param TPR array of true positive rates
* @param FPR array of false positive rates
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of TPR for each class.
*/
struct // PLR(Positive likelihood ratio)
{
  auto operator() (const float * TPR, const float * FPR, const int & Nclass)
  {
    std :: unique_ptr < float[] > PLR (new float[Nclass]);
    std :: transform(TPR, TPR + Nclass, FPR, PLR.get(), [](const float & tp, const float & tn){return tp / (tn + epsil);});
    return PLR;
  }
} get_PLR;

/**
* @brief Negative likelihood ratio
*
* @details Likelihood ratios are used for assessing the value of performing a
* diagnostic test. They use the sensitivity and specificity of the test to
* determine whether a test result usefully changes the probability that a condition
* (such as a disease state) exists. The first description of the use of likelihood
* ratios for decision rules was made at a symposium on information theory in 1954.
*
* ```python
* NLR = FNR / TNR
* ```
*
* @param FNR array of false negative rates
* @param TNR array of true negative rates
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of NLR for each class.
*/
struct // NLR(Negative likelihood ratio)
{
  auto operator() (const float * FNR, const float * TNR, const int & Nclass)
  {
    std :: unique_ptr < float[] > NLR (new float[Nclass]);
    std :: transform(FNR, FNR + Nclass, TNR, NLR.get(), [](const float & tp, const float & tn){return tp / (tn + epsil);});
    return NLR;
  }
} get_NLR;

/**
* @brief Diagnostic odds ratio
*
* @details The diagnostic odds ratio is a measure of the effectiveness of a
* diagnostic test. It is defined as the ratio of the odds of the test being
* positive if the subject has a disease relative to the odds of the test being
* positive if the subject does not have the disease.
*
* ```python
* DOR = PLR / NLR
* ```
*
* @param PLR array of positive likelihood ratio values.
* @param NLR array of negative likelihood ratio values.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of DOR scores for each class.
*/
struct // DOR(Diagnostic odds ratio)
{
  auto operator() (const float * PLR, const float * NLR, const int & Nclass)
  {
    std :: unique_ptr < float[] > DOR (new float[Nclass]);
    std :: transform(PLR, PLR + Nclass, NLR, DOR.get(), [](const float & tp, const float & tn){return tp / (tn + epsil);});
    return DOR;
  }
} get_DOR;

/**
* @brief Prevalence
*
* @details Prevalence is a statistical concept referring to the number of cases of a
* disease that are present in a particular population at a given time
* (Reference Likelihood).
*
* ```python
* PRE = P / POP
* ```
*
* @param P array of the number of positive samples for each class.
* @param POP array of total samples for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of PRE scores for each class.
*/
struct // PRE(Prevalence)
{
  auto operator() (const float * P, const float * POP, const int & Nclass)
  {
    std :: unique_ptr < float[] > PRE (new float[Nclass]);
    std :: transform(P, P + Nclass, POP, PRE.get(), [](const float & p, const float & pop){return p / (pop + epsil);});
    return PRE;
  }
} get_PRE;

/**
* @brief G-measure
*
* @details The geometric mean of precision and sensitivity,
* also known as Fowlkes–Mallows index.
*
* ```python
* G = sqrt(PPV * TPR)
* ```
*
* @param PPV array of positive predicted values.
* @param TPR array of true positive rates.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of G scores for each class.
*/
struct // G(G-measure geometric mean of precision and sensitivity)
{
  auto operator() (const float * PPV, const float * TPR, const int & Nclass)
  {
    std :: unique_ptr < float[] > G (new float[Nclass]);
    std :: transform(PPV, PPV + Nclass, TPR, G.get(), [](const float & i1, const float & i2){return std :: sqrt(i1 * i2);});
    return G;
  }
} get_G;

/**
* @brief Random accuracy
*
* @details The expected accuracy from a strategy of randomly guessing
* categories according to reference and response distributions.
*
* ```python
* RACC = (TOP * P) / POP**2
* ```
*
* @param TOP array of positive predicted values for each class.
* @param P array of true positive rates for each class.
* @param POP array of true positive rates for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of RACC scores for each class.
*/
struct // RACC(Random accuracy)
{
  auto operator() (const float * TOP, const float * P, const float * POP, const int & Nclass)
  {
    std :: unique_ptr < float[] > RACC (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      RACC[i] = (TOP[i] * P[i]) / (POP[i] * POP[i] + epsil);
    return RACC;
  }
} get_RACC;

/**
* @brief Error rate
*
* @details The error rate is the number of incorrect predictions from all predictions made.
*
* ```python
* ERR = (FP + FN) / (P + N) = (FP + FN) / (TP + TN + FP + FN) = 1 - ACC
* ```
*
* @param ACC array of accuracy scores for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of error rates for each class.
*/
struct // ERR(Error rate)
{
  auto operator() (const float * ACC, const int & Nclass)
  {
    std :: unique_ptr < float[] > ERR_ACC (new float[Nclass]);
    std :: transform(ACC, ACC + Nclass, ERR_ACC.get(), [](const float & acc){return 1.f - acc;});
    return ERR_ACC;
  }
} get_ERR_ACC;

/**
* @brief Random accuracy unbiased
*
* @details The expected accuracy from a strategy of randomly guessing categories
* according to the average of the reference and response distributions.
*
* ```python
* RACCU = ((TOP + P) / (2 * POP))**2
* ```
*
* @param TOP array of positive predicted values.
* @param P array of true positive rates.
* @param POP array of true positive rates.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of RACCU scores for each class.
*/
struct // RACCU(Random accuracy unbiased)
{
  auto operator() (const float * TOP, const float * P, const float * POP, const int & Nclass)
  {
    std :: unique_ptr < float[] > RACCU (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      RACCU[i] = ( (TOP[i] + P[i]) * (TOP[i] + P[i]) ) / (POP[i] * POP[i] * 4.f + epsil);
    return RACCU;
  }
} get_RACCU;

/**
* @brief Jaccard index
*
* @details The Jaccard index, also known as Intersection over Union and the
* Jaccard similarity coefficient (originally coined coefficient de communauté
* by Paul Jaccard), is a statistic used for comparing the similarity and
* diversity of sample sets.
*
* ```python
* J = TP / (TOP + P - TP)
* ```
*
* @param TP array of true positive values.
* @param TOP array of positive predicted values.
* @param P array of true positive rates.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of J scores for each class.
*/
struct // J(Jaccard index)
{
  auto operator() (const float * TP, const float * TOP, const float * P, const int & Nclass)
  {
    std :: unique_ptr < float[] > jaccard_index (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      jaccard_index[i] = TP[i] / (TOP[i] + P[i] - TP[i] + epsil);
    return jaccard_index;
  }
} get_jaccard_index;

/**
* @brief Information score
*
* @details The amount of information needed to correctly classify an example into
* class C, whose prior probability is p(C), is defined as −log2⁡(p(C)).
*
* ```python
* IS = -log2( (TP + FN)/POP ) + log2( TP / (TP + FP))
* ```
*
* @param TP array of true positive values.
* @param FP array of false positive values.
* @param FN array of false negative values.
* @param POP array of true positive rates.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of IS scores for each class.
*/
struct // IS(Information score)
{
  auto operator() (const float * TP, const float * FP, const float * FN, const float * POP, const int & Nclass)
  {
    std :: unique_ptr < float[] > IS (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      IS[i] = -std :: log2((TP[i] + FN[i]) / (POP[i] + epsil)) + (std :: log2(TP[i] / (TP[i] + FP[i] + epsil)));
    return IS;
  }
} get_IS;

/**
* @brief Confusion entropy
*
* @details CEN based upon the concept of entropy for evaluating classifier
* performances. By exploiting the misclassification information of confusion
* matrices, the measure evaluates the confusion level of the class distribution
* of misclassified samples. Both theoretical analysis and statistical results
* show that the proposed measure is more discriminating than accuracy and RCI
* while it remains relatively consistent with the two measures.
* Moreover, it is more capable of measuring how the samples of different classes
* have been separated from each other.
* Hence the proposed measure is more precise than the two measures and can
* substitute for them to evaluate classifiers in classification applications.
*
* @param confusion_matrix confusion matrix.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of CEN for each class.
*/
struct // CEN(Confusion entropy)
{
  auto operator() (const float * confusion_matrix, const int & Nclass)
  {
    std :: unique_ptr < float[] > CEN (new float[Nclass]);

    for (int i = 0; i < Nclass; ++i)
    {
      CEN[i] = 0.f;

      for (int j = 0; j < Nclass; ++j)
      {
        if (j != i)
        {
          float CEN_misclassification_calc = 0.f;

          for (int k = 0; k < Nclass; ++k)
            CEN_misclassification_calc += confusion_matrix[i * Nclass + k] + confusion_matrix[ k * Nclass + i];

          const float P_j_k = confusion_matrix[i * Nclass + j] / (CEN_misclassification_calc + epsil);
          const float P_k_j = confusion_matrix[j * Nclass + i] / (CEN_misclassification_calc + epsil);

          CEN[i] += P_j_k != 0.f ? P_j_k * (std :: log(P_j_k) / std :: log(2 * (Nclass - 1))) : 0.f;
          CEN[i] += P_k_j != 0.f ? P_k_j * (std :: log(P_k_j) / std :: log(2 * (Nclass - 1))) : 0.f;
        }
      }

      CEN[i] = -CEN[i];
    }

    return CEN;
  }
} get_CEN;

/**
* @brief Modified confusion entropy
*
* @details Modified version of CEN
*
* @param confusion_matrix confusion matrix.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of MCEN for each class.
*/
struct // MCEN(Modified confusion entropy)
{
  auto operator() (const float * confusion_matrix, const int & Nclass)
  {
    std :: unique_ptr < float[] > MCEN (new float[Nclass]);

    for (int i = 0; i < Nclass; ++i)
    {
      MCEN[i] = 0.f;

      for (int j = 0; j < Nclass; ++j)
      {
        if (j != i)
        {
          float CEN_misclassification_calc = 0.f;

          for (int k = 0; k < Nclass; ++k)
            CEN_misclassification_calc += confusion_matrix[i * Nclass + k] + confusion_matrix[ k * Nclass + i];

          CEN_misclassification_calc -= confusion_matrix[i * Nclass + i];

          const float P_j_k = confusion_matrix[i * Nclass + j] / (CEN_misclassification_calc + epsil);
          const float P_k_j = confusion_matrix[j * Nclass + i] / (CEN_misclassification_calc + epsil);

          MCEN[i] += P_j_k != 0.f ? P_j_k * (std :: log(P_j_k) / std :: log(2 * (Nclass - 1))) : 0.f;
          MCEN[i] += P_k_j != 0.f ? P_k_j * (std :: log(P_k_j) / std :: log(2 * (Nclass - 1))) : 0.f;
        }
      }

      MCEN[i] = -MCEN[i];
    }
    return MCEN;
  }
} get_MCEN;

/**
* @brief Area under the ROC curve
*
* @details The area under the curve (often referred to as simply the AUC) is
* equal to the probability that a classifier will rank a randomly chosen positive
* instance higher than a randomly chosen negative one (assuming 'positive' ranks
* higher than 'negative').
* Thus, AUC corresponds to the arithmetic mean of sensitivity and specificity values
* of each class.
*
* ```python
* AUC = (TNR + TPR) / 2
* ```
*
* @param TNR array of true negative rates
* @param TPR array of true positive rates
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of AUC for each class.
*/
struct // AUC(Area Under the ROC curve)
{
  auto operator() (const float * TNR, const float * TPR, const int & Nclass)
  {
    std :: unique_ptr < float[] > AUC (new float[Nclass]);
    std :: transform(TNR, TNR + Nclass, TPR, AUC.get(), [](const float & tnr, const float & tpr){return (tnr + tpr) * .5f;});
    return AUC;
  }

} get_AUC;

/**
* @brief Distance index
*
* @details Euclidean distance of a ROC point from the top left corner of the
* ROC space, which can take values between 0 (perfect classification) and sqrt(2).
*
* ```python
* dInd = sqrt((1 - TNR)**2 + (1 - TPR)**2)
* ```
*
* @param TNR array of true negative rates
* @param TPR array of true positive rates
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of dInd for each class.
*/
struct // dInd(Distance index)
{
  auto operator() (const float * TNR, const float * TPR, const int & Nclass)
  {
    std :: unique_ptr < float[] > dIND (new float[Nclass]);
    std :: transform(TNR, TNR + Nclass, TPR, dIND.get(), [](const float & tnr, const float & tpr){return std :: sqrt( (1.f - tnr) * (1.f - tnr) + (1.f - tpr) * (1.f - tpr) );});
    return dIND;
  }

} get_dIND;

/**
* @brief Similarity index
*
* @details sInd is comprised between 0 (no correct classifications) and
* 1 (perfect classification).
*
* ```python
* sInd = 1 - dInd
* ```
*
* @param dInd array of distance indexes for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of sInd for each class.
*/
struct // sInd(Similarity index)
{
  auto operator() (const float * dIND, const int & Nclass)
  {
    std :: unique_ptr < float[] > sIND (new float[Nclass]);
    std :: transform(dIND, dIND + Nclass, sIND.get(), [](const float & dind){return 1.f - (dind / std :: sqrt(2));});
    return sIND;
  }

} get_sIND;

/**
* @brief Discriminant power
*
* @details Discriminant power (DP) is a measure that summarizes sensitivity
* and specificity.
* The DP has been used mainly in feature selection over imbalanced data.
*
* ```python
* DP = (sqrt(3) / π ) * (log10(TPR / (1 - TPR)) + log10(TNR / (1 - TNR)))
* ```
*
* @param TPR array of true positive rates
* @param TNR array of true negative rates
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of DP for each class.
*/
struct // DP(Discriminant power)
{
  auto operator() (const float * TPR, const float * TNR, const int & Nclass)
  {
    std :: unique_ptr < float[] > DP (new float[Nclass]);
    std :: transform(TPR, TPR + Nclass, TNR, DP.get(), [](const float & tpr, const float & tnr){return std :: sqrt(3) / 3.14f * (std :: log10(tpr / (1.f - tpr)) + std :: log10(tnr / (1.f - tnr)));});
    return DP;
  }

} get_DP;

/**
* @brief Youden index
*
* @details Youden’s index evaluates the algorithm’s ability to avoid failure;
* it’s derived from sensitivity and specificity and denotes a linear correspondence
* balanced accuracy.
* As Youden’s index is a linear transformation of the mean sensitivity and specificity,
* its values are difficult to interpret, we retain that a higher value of Y
* indicates better ability to avoid failure.
* Youden’s index has been conventionally used to evaluate tests diagnostic,
* improve the efficiency of Telemedical prevention.
*
* ```python
* Y = BM = TPR + TNR - 1
* ```
*
* @param BM array of bookmaker indexes for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of Y for each class.
*/
struct // Y(Youden index)
{
  auto operator() (const float * BM, const int & Nclass)
  {
    std :: unique_ptr < float[] > Y (new float[Nclass]);
    std :: copy_n(BM, Nclass, Y.get());
    return Y;
  }

} get_Y;

/**
* @brief Positive likelihood ratio interpretation
*
* @details The score follows the ranges
* - PLR < 1 Negligible
* - 1 < PLR < 5 Poor
* - 5 < PLR < 10 Fair
* - PLR > 10 Good
*
* @param PLR array of positive likelihood ratio values.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of PLRI for each class.
*/
struct // PLRI(Positive likelihood ratio interpretation)
{
  auto operator() (const float * PLR, const int & Nclass)
  {
    std :: unique_ptr < float[] > PLRI (new float[Nclass]);
    std :: transform(PLR, PLR + Nclass, PLRI.get(), [](const float & plr){return std :: isnan(plr) || std :: isinf(plr) ? -1.f : plr < 1.f ? 0.f : plr >= 1.f && plr < 5.f ? 1.f : plr >= 5.f && plr < 10.f ? 2.f : 3.f;});
    return PLRI;
  }

} get_PLRI;

/**
* @brief Negative likelihood ratio interpretation
*
* @details The score follows the ranges
* - 0.5 < NLR < 1 Negligible
* - 0.2 < NLR < 0.5 Poor
* - 0.1 < NLR < 0.2 Fair
* - NLR > 0.1 Good
*
* @param NLR array of negative likelihood ratio values for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of NLRI for each class.
*/
struct // NLRI(Negative likelihood ratio interpretation)
{
  auto operator() (const float * NLR, const int & Nclass)
  {
    std :: unique_ptr < float[] > NLRI (new float[Nclass]);
    std :: transform(NLR, NLR + Nclass, NLRI.get(), [](const float & nlr){return std :: isnan(nlr) || std :: isinf(nlr) ? -1.f : nlr < .1f ? 0.f : nlr >= .1f && nlr < .2f ? 1.f : nlr >= .2f && nlr < .5f ? 2.f : 3.f;});
    return NLRI;
  }

} get_NLRI;

/**
* @brief Discriminant power interpretation
*
* @details The score follows the ranges
* - DPI < 1 Poor
* - 1 < DPI < 2 Limited
* - 2 < DPI < 3 Fair
* - DPI > 3 Good
*
* @param DP array of discriminant power values for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of DPI for each class.
*/
struct // DPI(Discriminant power interpretation)
{
  auto operator() (const float * DP, const int & Nclass)
  {
    std :: unique_ptr < float[] > DPI (new float[Nclass]);
    std :: transform(DP, DP + Nclass, DPI.get(), [](const float & dp){return std :: isnan(dp) || std :: isinf(dp) ? -1.f : dp < 1.f ? 0.f : dp >= 1.f && dp < 2.f ? 1.f : dp >= 2.f && dp < 3.f ? 2.f : 3.f;});
    return DPI;
  }

} get_DPI;

/**
* @brief AUC value interpretation
*
* @details The score follows the ranges
* - 0.5 < AUCI > 0.6 Poor
* - 0.6 < AUCI < 0.7 Fair
* - 0.7 < AUCI < 0.8 Good
* - 0.8 < AUCI < 0.9 Very good
* - 0.9 < AUCI < 1.0 Excellent
*
* @param AUC array of area under the curve values for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of AUCI for each class.
*/
struct // AUCI(AUC value interpretation)
{
  auto operator() (const float * AUC, const int & Nclass)
  {
    std :: unique_ptr < float[] > AUCI (new float[Nclass]);
    std :: transform(AUC, AUC + Nclass, AUCI.get(), [](const float & auc){return std :: isnan(auc) || std :: isinf(auc) ? -1.f : auc < .6f ? 0.f : auc >= .6 && auc < .7f ? 1.f : auc >= .7f && auc < .8f ? 2.f : 3.f;});
    return AUCI;
  }

} get_AUCI;

/**
* @brief Gini index
*
* @details A chance-standardized variant of the AUC is
* given by Gini coefficient, taking values between 0 (no difference between the
* score distributions of the two classes) and 1 (complete separation between the
* two distributions).
* Gini coefficient is widespread use metric in imbalanced data learning.
*
* ```python
* GI = 2 * AUC - 1
* ```
*
* @param AUC array of area under the curve values for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of Gini-index scores for each class
*/
struct // GI(Gini index)
{
  auto operator() (const float * AUC, const int & Nclass)
  {
    std :: unique_ptr < float[] > GI (new float[Nclass]);
    std :: transform(AUC, AUC + Nclass, GI.get(), [](const float & auc){return 2.f * auc - 1.f;});
    return GI;
  }

} get_GI;

/**
* @brief Lift score
*
* @details In the context of classification, lift compares model predictions to
* randomly generated predictions.
* Lift is often used in marketing research combined with gain and lift charts
* as a visual aid.
*
* ```python
* LS = PPV / PRE
* ```
*
* @param PPV array of positive predicted values for each class.
* @param PRE array of prevalence scores for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of LS scores for each class
*/
struct // LS(Lift score)
{
  auto operator() (const float * PPV, const float * PRE, const int & Nclass)
  {
    std :: unique_ptr < float[] > LS (new float[Nclass]);
    std :: transform(PPV, PPV + Nclass, PRE, LS.get(), [](const float & ppv, const float & pre){return ppv / (pre + epsil);});
    return LS;
  }

} get_LS;

/**
* @brief Automatic/Manual
*
* @details Difference between automatic and manual classification i.e.,
* the difference between positive outcomes and of positive samples.
*
* ```python
* AM = TOP - P = (TP + FP) - (TP + FN)
* ```
*
* @param TOP array of positive predicted values for each class.
* @param P array of the number of positive samples for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of AM scores for each class
*/
struct // AM(Difference between automatic and manual classification)
{
  auto operator() (const float * TOP, const float * P, const int & Nclass)
  {
    std :: unique_ptr < float[] > AM (new float[Nclass]);
    std :: transform(TOP, TOP + Nclass, P, AM.get(), [](const float & top, const float & p){return top - p;});
    return AM;
  }

} get_AM;

/**
* @brief Optimized precision
*
* @details Optimized precision is a type of hybrid threshold metric and has
* been proposed as a discriminator for building an optimized heuristic classifier.
* This metric is a combination of accuracy, sensitivity and specificity metrics.
* The sensitivity and specificity metrics were used for stabilizing and optimizing
* the accuracy performance when dealing with an imbalanced class of two-class problems.
*
* ```python
* OP = ACC - abs(TNR - TPR) / abs(TNR + TPR)
* ```
*
* @param ACC array of accuracy scores for each class.
* @param TPR array of true positive rates for each class.
* @param TNR array of true negative rates for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of OP scores for each class
*/
struct // OP(Optimized precision)
{
  auto operator() (const float * ACC, const float * TPR, const float * TNR, const int & Nclass)
  {
    std :: unique_ptr < float[] > OP (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      OP[i] = ACC[i] - std :: fabs(TNR[i] - TPR[i]) / (TPR[i] + TNR[i] + epsil);

    return OP;
  }

} get_OP;

/**
* @brief Index of balanced accuracy
*
* @details The method combines an unbiased index of its overall accuracy and a
* measure about how dominant is the class with the highest individual accuracy rate.
*
* ```python
* IBAα = (1 + α * (TPR - TNR)) * TNR * TPR
* ```
*
* @param TPR array of true positive rates for each class.
* @param TNR array of true negative rates for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of IBA scores for each class
*/
struct // IBA(Index of balanced accuracy)
{
  auto operator() (const float * TPR, const float * TNR, const int & Nclass)
  {
    std :: unique_ptr < float[] > IBA (new float[Nclass]);
    std :: transform(TPR, TPR + Nclass, TNR, IBA.get(), [](const float & tpr, const float & tnr){return (1.f + tpr - tnr) * tpr * tnr;});
    return IBA;
  }

} get_IBA;

/**
* @brief G-mean
*
* @details Geometric mean of specificity and sensitivity.
*
* ```python
* GM = sqrt(TPR * TNR)
* ```
*
* @param TNR array of true negative rates for each class.
* @param TPR array of true positive rates for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of GM scores for each class
*/
struct // GM(G-mean geometric mean of specificity and sensitivity)
{
  auto operator() (const float * TNR, const float * TPR, const int & Nclass)
  {
    std :: unique_ptr < float[] > GM (new float[Nclass]);
    std :: transform(TNR, TNR + Nclass, TPR, GM.get(), [](const float & tnr, const float & tpr){return std :: sqrt(tnr * tpr);});
    return GM;
  }

} get_GM;

/**
* @brief Yule's Q
*
* @details In statistics, Yule's Q, also known as the coefficient of colligation,
* is a measure of association between two binary variables.
*
* ```python
* OR = (TP * TN) / (FP * FN)
* Q = (OR - 1) / (OR + 1)
* ```
*
* @param TP array of true positives for each class.
* @param TN array of true negatives for each class.
* @param FP array of false positives for each class.
* @param FN array of false negative for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of Q scores for each class
*/
struct // Q(Yule Q - coefficient of colligation)
{
  auto operator() (const float * TP, const float * TN, const float * FP, const float * FN, const int & Nclass)
  {
    std :: unique_ptr < float[] > Q (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
    {
      const float OR = (TP[i] * TN[i]) / (FP[i] * FN[i] + epsil);
      Q[i] = (OR - 1.f) / (OR + 1.f);
    }
    return Q;
  }

} get_Q;

/**
* @brief Adjusted G-mean
*
* @details An adjusted version of the geometric mean of specificity and sensitivity.
*
* ```python
* Nn = N / POP
* AGM = (GM + TNR * Nn) / (1 + Nn) if TPR > 0 else 0
* ```
*
* @param TPR array of true positive rates for each class.
* @param TNR array of true negative rates for each class.
* @param GM array of geometric means for each class.
* @param N array of number of negative samples for each class.
* @param POP array of total samples for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of AGM score values for each class.
*/
struct // AGM(Adjusted geometric mean)
{
  auto operator() (const float * TPR, const float * TNR, const float * GM, const float * N, const float * POP, const int & Nclass)
  {
    std :: unique_ptr < float[] > AGM (new float[Nclass]);

    for (int i = 0; i < Nclass; ++i)
    {
      if (POP[i] != 0.f)
      {
        AGM[i] = TPR[i] == 0.f ? 0.f : (GM[i] + TNR[i] * N[i] / (POP[i] + epsil)) / (1.f + N[i] / (POP[i] + epsil));
      }
      else
        AGM[i] = -1.f;
    }

    return AGM;
  }

} get_AGM;

/**
* @brief Matthews correlation coefficient interpretation
*
* @details MCC is a confusion matrix method of calculating the Pearson
* product-moment correlation coefficient (not to be confused with Pearson's C).
* Therefore, it has the same interpretation.
* The score follows the ranges
* - MCCI < 0.3 Negligible
* - 0.3 < MCCI < 0.5 Weak
* - 0.5 < MCCI < 0.7 Moderate
* - 0.7 < MCCI < 0.9 Strong
* - 0.9 < MCCI < 1.0 Very Strong
*
* @param MCC array of Matthews correlation coefficients for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of MCCI scores for each class.
*/
struct // MCCI(Matthews correlation coefficient interpretation)
{
  auto operator() (const float * MCC, const int & Nclass)
  {
    std :: unique_ptr < float[] > MCCI (new float[Nclass]);
    std :: transform(MCC, MCC + Nclass, MCCI.get(), [](const float & mcc){return std :: isnan(mcc) || std :: isinf(mcc) ? -1.f : mcc < .3f ? 0.f : mcc >= .3f && mcc < .5f ? 1.f : mcc >= .5f && mcc < .7f ? 2.f : mcc >= .7 && mcc < .9f ? 3.f : 4.f;});
    return MCCI;
  }

} get_MCCI;

/**
* @brief Adjusted F-score
*
* @details The F-measures used only three of the four elements of the
* confusion matrix and hence two classifiers with different TNR values
* may have the same F-score.
* Therefore, the AGF metric is introduced to use all elements of
* the confusion matrix and provide more weights to samples which are
* correctly classified in the minority class.
*
* ```python
* F2 = 5 * (PPV * TPR) / ((4 * PPV) + TPR)
* InvF0.5 = (1 + 0.5**2) * (NPV * TNR) / ((0.5**2 * NPV) + TNR)
* AGF = sqrt(F2 * invF0.5)
* ```
*
* @param TP array of true positives
* @param FP array of false positives
* @param FN array of false negative
* @param TN array of true negatives
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of AGF scores for each class.
*/
struct // AGF(Adjusted F-score)
{
  auto operator() (const float * TP, const float * FP, const float * FN, const float * TN, const int & Nclass)
  {
    std :: unique_ptr < float[] > AGF (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
    {
      const float F2 = (5.f * TP[i]) / (5.f * TP[i] + FP[i] + 4.f * FN[i] + epsil);
      const float F05_inv = (1.25f * TN[i]) / (1.25f * TN[i] + FN[i] + .25f * FP[i] + epsil);
      AGF[i] = std :: sqrt(F2 * F05_inv);
    }

    return AGF;
  }

} get_AGF;

/**
* @brief Overlap coefficient
*
* @details The overlap coefficient, or Szymkiewicz–Simpson coefficient, is a similarity
* measure that measures the overlap between two finite sets.
* It is defined as the size of the intersection divided by the smaller of the size of
* the two sets.
*
* ```python
* OC = TP / min(TOP, P) = max(PPV, TPR)
* ```
*
* @param TP array of true positive values for each class.
* @param TOP array of positive predicted values for each class.
* @param P array of the number of positive samples for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of OC values for each class.
*/
struct // OC(Overlap coefficient)
{
  auto operator() (const float * TP, const float * TOP, const float * P, const int & Nclass)
  {
    std :: unique_ptr < float[] > OC (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
    {
      OC[i] = TP[i] / (std :: min(TOP[i], P[i]) + epsil);
    }

    return OC;
  }

} get_OC;

/**
* @brief Otsuka-Ochiai coefficient
*
* @details In biology, there is a similarity index, known as the Otsuka-Ochiai
* coefficient named after Yanosuke Otsuka and Akira Ochiai, also known as the
* Ochiai-Barkman or Ochiai coefficient.
* If sets are represented as bit vectors, the Otsuka-Ochiai coefficient can be
* seen to be the same as the cosine similarity.
*
* ```python
* OOC = TP / sqrt(TOP * P)
* ```
*
* @param TP array of true positive values for each class.
* @param TOP array of positive predicted values for each class.
* @param P array of the number of positive samples for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of OOC values for each class.
*/
struct // OOC(Otsuka-Ochiai coefficient)
{
  auto operator() (const float * TP, const float * TOP, const float * P, const int & Nclass)
  {
    std :: unique_ptr < float[] > OOC (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
    {
      OOC[i] = TP[i] / (std :: sqrt(TOP[i] * P[i]) + epsil);
    }

    return OOC;
  }

} get_OOC;

/**
* @brief Area under the PR curve
*
* @details A PR curve is plotting precision against recall.
* The precision recall area under curve (AUPR) is just the area under the PR curve.
* The higher it is, the better the model is.
*
* ```python
* AUPR = (TPR + PPV) / 2
* ```
*
* @param PPV array of positive predicted values for each class.
* @param TPR array of true positive rates for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of AUPR values for each class.
*/
struct // AUPR(Area under the PR curve)
{
  auto operator() (const float * PPV, const float * TPR, const int & Nclass)
  {
    std :: unique_ptr < float[] > AUPR (new float[Nclass]);
    std :: transform(PPV, PPV + Nclass, TPR, AUPR.get(), [](const float & ppv, const float & tpr){return (ppv + tpr) * .5f;});

    return AUPR;
  }

} get_AUPR;

/**
* @brief Bray-Curtis dissimilarity
*
* @details In ecology and biology, the Bray–Curtis dissimilarity, named
* after J. Roger Bray and John T. Curtis, is a statistic used to quantify the
* compositional dissimilarity between two different sites, based on counts at each site.
*
* ```python
* BCD = abs(AM) / sum(TOP + P)
* ```
*
* @param TOP array of positive predicted values for each class.
* @param P array of the number of positive samples for each class.
* @param AM array of Automatic/Manual differences for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of BCD scores for each class.
*/
struct // BCD(Bray-Curtis dissimilarity)
{
  auto operator() (const float * TOP, const float * P, const float * AM, const int & Nclass)
  {
    std :: unique_ptr < float[] > BCD (new float[Nclass]);
    const float s = std :: accumulate(TOP, TOP + Nclass, 0.f) + std :: accumulate(P, P + Nclass, 0.f) + epsil;
    std :: transform(AM, AM + Nclass, BCD.get(), [&](const float & am){return std :: fabs(am) / s;});
    return BCD;
  }

} get_BCD;


#endif // __class_stats_h__
