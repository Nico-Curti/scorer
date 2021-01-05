#ifndef __overall_stats_h__
#define __overall_stats_h__

#include <common_stats.h>

/// @cond DEF
#ifdef _MSC_VER

  #ifndef __unused
    #define __unused
  #endif

#else // Not Visual Studio Compiler

  #ifndef __unused
    #define __unused __attribute__((__unused__))
  #endif

#endif
/// @endcond

/**
* @brief Overall Accuracy
*
* @details
* ```python
* overall_accuracy = sum(TP) / POP
* ```
*
* @param TP array of true positives for each class.
* @param TOP array of positive predicted values for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The overall accuracy score.
*/
struct // Overall ACC
{
  auto operator() (const float * TP, const float * POP, const int & Nclass)
  {
    return std :: accumulate(TP, TP + Nclass, 0.f) / (POP[0] + epsil);
  }
} get_overall_accuracy;

/**
* @brief Overall random accuracy unbiased.
*
* @details
* ```python
* overall_random_accuracy = sum(random_accuracy_unbiased)
* ```
*
* @param RACCU array of random accuracies unbiased for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The overall random accuracy unbiased score.
*/
struct // Overall RACCU
{
  auto operator() (const float * RACCU, const int & Nclass)
  {
    return std :: accumulate(RACCU, RACCU + Nclass, 0.f);
  }
} get_overall_random_accuracy_unbiased;

/**
* @brief Overall random accuracy
*
* @details
* ```python
* overall_random_accuracy = sum(random_accuracy)
* ```
*
* @param RACC array of random accuracies for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The overall random accuracy score.
*/
struct // Overall RACC
{
  auto operator() (const float * RACC, const int & Nclass)
  {
    return std :: accumulate(RACC, RACC + Nclass, 0.f);
  }
} get_overall_random_accuracy;

/**
* @brief Kappa
*
* @details Kappa is a statistic that measures inter-rater agreement
* for qualitative (categorical) items.
* It is generally thought to be a more robust measure than simple percent agreement
* calculation, as kappa takes into account the possibility of the agreement occurring
* by chance.
*
* ```python
* Kappa = (overall_ACC - overall_RACC) / (1 - overall_RACC)
* ```
*
* @param overall_random_accuracy Overall RACC value.
* @param overall_accuracy Overall ACC value.
*
* @return The Kappa overall score.
*/
struct // Kappa
{
  auto operator() (const float & overall_random_accuracy, const float & overall_accuracy)
  {
    return (overall_accuracy - overall_random_accuracy) / (1.f - overall_random_accuracy + epsil);
  }
} get_overall_kappa;

/**
* @brief Utility function for future scores.
*
* @details It compute the simple formula:
*
* ```python
* pc = sum((TOP + P)/(2 * POP)**2)
* ```
*
* @param P array of the number of positive samples for each class.
* @param TOP array of positive predicted values for each class.
* @param POP array of total samples for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The PC_PI score.
*/
struct // PC_PI
{
  auto operator() (const float * P, const float * TOP, const float * POP, const int & Nclass)
  {
    float res = 0.f;
    for (int i = 0; i < Nclass; ++i)
      res += ( (P[i] + TOP[i]) * (P[i] + TOP[i]) ) / ( 4.f * POP[i] * POP[i] + epsil );
    return res;
  }
} get_PC_PI;

/**
* @brief Utility function for future scores.
*
* @details It compute the simple formula:
*
* ```python
* pi = (TOP * P) / (2 * POP)
* pc = 1 / (abs(C) - 1) * sum(pi * (1 - pi))
* ```
*
* @param P array of the number of positive samples for each class.
* @param TOP array of positive predicted values for each class.
* @param POP array of total samples for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The PC_AC1 score.
*/
struct // PC_AC1
{
  auto operator() (const float * P, const float * TOP, const float * POP, const int & Nclass)
  {
    float AC1 = 0.f;
    for (int i = 0; i < Nclass; ++i)
    {
      const float pi = (P[i] + TOP[i]) / (2.f * POP[i] + epsil);
      AC1 += pi * (1.f - pi);
    }
    return AC1 / (Nclass - 1 + epsil);
  }
} get_PC_AC1;

/**
* @brief One over classes.
*
* @details It is just an utility function for future scores.
*
* @param classes array of classes found (this variable is useless in the computation but it is necessary for the graph estimation).
* @param Nclass size of classes array (aka number of classes)
*
* @return The PC_S score
*/
struct // PC_S
{
  // we need "classes" because the auto-generated code must put this function AFTER the Nclass evalution
  auto operator() (__unused const float * classes, const int & Nclass)
  {
    return 1.f / static_cast < float >(Nclass);
  }
} get_PC_S;

/**
* @brief Scott's Pi
*
* @details Scott's pi (named after William A. Scott) is a statistic for measuring
* inter-rater reliability for nominal data in communication studies.
* Textual entities are annotated with categories by different annotators, and various
* measures are used to assess the extent of agreement between the annotators, one of
* which is Scott's pi. Since automatically annotating text is a popular problem in
* natural language processing, and the goal is to get the computer program that is
* being developed to agree with the humans in the annotations it creates, assessing
* the extent to which humans agree with each other is important for establishing a
* reasonable upper limit on computer performance.
*
* ```python
* pc = sum((TOP + P) / (2 * POP)**2)
* π = (overall_accuracy - pc) / (1 - pc)
* ```
*
* @param PC_PI pc score in the formula.
* @param overall_accuracy Overall accuracy score.
*
* @return
*/
struct // Scott PI
{
  auto operator() (const float & PC_PI, const float & overall_accuracy)
  {
    return (overall_accuracy - PC_PI) / (1.f - PC_PI + epsil);
  }
} get_PI;

/**
* @brief Gwet's AC1
*
* @details AC1 was originally introduced by Gwet in 2001 (Gwet, 2001).
* The interpretation of AC1 is similar to generalized kappa (Fleiss, 1971),
* which is used to assess inter-rater reliability when there are multiple raters.
* Gwet (2002) demonstrated that AC1 can overcome the limitations that kappa is sensitive
* to trait prevalence and rater's classification probabilities (i.e., marginal probabilities),
* whereas AC1 provides more robust measure of inter-rater reliability.
*
* ```python
* AC1 = (overall_accuracy - pc) / (1 - pc)
* ```
*
* @param PC_AC1 the pc in the formula.
* @param overall_accuracy Overall accuracy score.
*
* @return The Gwet's AC1 score.
*/
struct // Get AC1
{
  auto operator() (const float & PC_AC1, const float & overall_accuracy)
  {
    return (overall_accuracy - PC_AC1) / (1.f - PC_AC1 + epsil);
  }
} get_AC1;

/**
* @brief Bennett's S
*
* @details Bennett, Alpert & Goldstein’s S is a statistical measure of inter-rater agreement.
* It was created by Bennett et al. in 1954. Bennett et al. suggested adjusting inter-rater
* reliability to accommodate the percentage of rater agreement that might be expected
* by chance was a better measure than a simple agreement between raters.
*
* ```python
* pc = 1 / abs(C)
* S = (overall_accuracy - pc) / (1 - pc)
* ```
*
* @param PC_S one over classes.
* @param overall_accuracy Overall accuracy score.
*
* @return The Bennett's S score.
*/
struct // Bennett S
{
  auto operator() (const float & PC_S, const float & overall_accuracy)
  {
    return (overall_accuracy - PC_S) / (1.f - PC_S + epsil);
  }
} get_S;

/**
* @brief Kappa standard error
*
* @details The standard error(s) of the Kappa coefficient was obtained by Fleiss (1969)
*
* ```python
* Kappa_se = sqrt((overall_accuracy * (1 - overall_random_accuracy)) / (1 - overall_random_accuracy)**2)
* ```
*
* @param overall_accuracy Overall ACC value.
* @param overall_random_accuracy_unbiased Overall RACCU value.
* @param POP array of total samples for each class.
*
* @return The Kappa standard error overall score.
*/
struct // Kappa Standard Error
{
  auto operator() (const float & overall_accuracy, const float & overall_random_accuracy, const float * POP)
  {
    return std :: sqrt( (overall_accuracy * (1.f - overall_accuracy) ) / (POP[0] * (1.f - overall_random_accuracy) * (1.f - overall_random_accuracy) + epsil) );
  }
} get_kappa_SE;

/**
* @brief Kappa unbiased
*
* @details The unbiased kappa value is defined in terms of total accuracy
* and a slightly different computation of expected likelihood that averages the
* reference and response probabilities.
*
* ```python
* Kappa_unbiased = (overall_ACC - overall_RACCU) / (1 - overall_RACC)
* ```
*
* @param overall_random_accuracy_unbiased Overall RACCU value.
* @param overall_accuracy Overall ACC value.
*
* @return The Kappa unbiased overall score.
*/
struct // Kappa Unbiased
{
  auto operator() (const float & overall_random_accuracy_unbiased, const float & overall_accuracy)
  {
    return (overall_accuracy - overall_random_accuracy_unbiased) / (1.f - overall_random_accuracy_unbiased + epsil);
  }
} get_kappa_unbiased;

/**
* @brief Kappa no prevalence
*
* @details The kappa statistic adjusted for prevalence.
*
* @details
* ```python
* Kappa_no_prevalence = 2 * overall_ACC - 1
* ```
*
* @param overall_accuracy Overall ACC value.
*
* @return The Kappa without prevalence overall score.
*/
struct // Kappa No Prevalence
{
  auto operator() (const float & overall_accuracy)
  {
    return 2.f * overall_accuracy - 1.f;
  }
} get_kappa_no_prevalence;

/**
* @brief Kappa 95% CI
*
* @details Kappa 95% Confidence (upper) Interval
*
* @details
* ```python
* Kappa_ci = overall_kappa + 1.96 * kappa_SE
* ```
*
* @param overall_kappa Kappa overall score.
* @param kappa_SE kappa standard error score.
*
* @return The Kappa 95% CI (upper bound) score.
*/
struct // Kappa 95% CI up
{
  auto operator() (const float & overall_kappa, const float & kappa_SE)
  {
    return overall_kappa + 1.96 * kappa_SE;
  }
} get_kappa_CI_up;

/**
* @brief Kappa 95% CI
*
* @details Kappa 95% Confidence (lower) Interval
*
* @details
* ```python
* Kappa_ci = overall_kappa - 1.96 * kappa_SE
* ```
*
* @param overall_kappa Kappa overall score.
* @param kappa_SE kappa standard error score.
*
* @return The Kappa 95% CI (lower bound) score.
*/
struct // Kappa 95% CI down
{
  auto operator() (const float & overall_kappa, const float & kappa_SE)
  {
    return overall_kappa - 1.96 * kappa_SE;
  }
} get_kappa_CI_down;

/**
* @brief Standard error
*
* @details The standard error (SE) of a statistic (usually an estimate of a parameter)
* is the standard deviation of its sampling distribution or an estimate of that
* standard deviation.
*
* ```python
* SE =sqrt(overall_accuracy * (1 - overall_accuracy) / POP)
* ```
*
* @param overall_accuracy Overall accuracy score.
* @param POP array of total samples for each class.
*
* @return The accuracy standard error score.
*/
struct // Standard Error
{
  auto operator() (const float & overall_accuracy, const float * POP)
  {
    return std :: sqrt( (overall_accuracy * (1.f - overall_accuracy)) / (POP[0] + epsil));
  }
} get_overall_accuracy_se;

/**
* @brief 95% CI (upper bound)
*
* @details In statistics, a confidence interval (CI) is a type of interval estimate
* (of a population parameter) that is computed from the observed data.
* The confidence level is the frequency (i.e., the proportion) of possible confidence
* intervals that contain the true value of their corresponding parameter.
* In other words, if confidence intervals are constructed using a given confidence
* level in an infinite number of independent experiments, the proportion of those intervals
* that contain the true value of the parameter will match the confidence level.
*
* @details
* ```python
* CI = overall_accuracy + 1.96 * overall_accuracy_se
* ```
*
* @param overall_accuracy Overall accuracy score.
* @param overall_accuracy_se Overall standard error score.
*
* @return The upper bound CI.
*/
struct // 95% CI up
{
  auto operator() (const float & overall_accuracy, const float & overall_accuracy_se)
  {
    return overall_accuracy + 1.96f * overall_accuracy_se;
  }
} get_overall_accuracy_ci_up;

/**
* @brief 95% CI (lower bound)
*
* @details In statistics, a confidence interval (CI) is a type of interval estimate
* (of a population parameter) that is computed from the observed data.
* The confidence level is the frequency (i.e., the proportion) of possible confidence
* intervals that contain the true value of their corresponding parameter.
* In other words, if confidence intervals are constructed using a given confidence
* level in an infinite number of independent experiments, the proportion of those intervals
* that contain the true value of the parameter will match the confidence level.
*
* @details
* ```python
* CI = overall_accuracy - 1.96 * overall_accuracy_se
* ```
*
* @param overall_accuracy Overall accuracy score.
* @param overall_accuracy_se Overall standard error score.
*
* @return The lower bound CI.
*/
struct // 95% CI down
{
  auto operator() (const float & overall_accuracy, const float & overall_accuracy_se)
  {
    return overall_accuracy - 1.96f * overall_accuracy_se;
  }
} get_overall_accuracy_ci_down;

/**
* @brief Chi-squared
*
* @details Pearson's chi-squared test is a statistical test applied to sets of
* categorical data to evaluate how likely it is that any observed difference between
* the sets arose by chance. It is suitable for unpaired data from large samples.
*
* @param confusion_matrix Confusion matrix.
* @param TOP array of positive predicted values for each class.
* @param P array of true positive rates for each class.
* @param POP array of true positive rates for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The Chi-Squared score.
*/
struct // Chi-Squared
{
  auto operator() (const float * confusion_matrix, const float * TOP, const float * P, const float * POP, const int & Nclass)
  {
    float res = 0.f,
          expected;
    for (int i = 0; i < Nclass; ++i)
      for (int j = 0; j < Nclass; ++j)
      {
        expected = (TOP[j] * P[i]) / (POP[i] + epsil);
        res += (confusion_matrix[i * Nclass + j] - expected) * (confusion_matrix[i * Nclass + j] - expected) / (expected + epsil);
      }
    return res;
  }
} get_chi_square;

/**
* @brief Phi-squared
*
* @details In statistics, the phi coefficient (or mean square contingency coefficient)
* is a measure of association for two binary variables. Introduced by Karl Pearson,
* this measure is similar to the Pearson correlation coefficient in its interpretation.
* In fact, a Pearson correlation coefficient estimated for two binary variables will return
* the phi coefficient.
*
* ```python
* phi**2 = chi**2 / POP
* ```
*
* @param chi_square Chi-Squared score.
* @param POP array of true positive rates for each class.
*
* @return The Phi-squared score.
*/
struct // Phi-Squared
{
  auto operator() (const float & chi_square, const float * POP)
  {
    return chi_square / (POP[0] + epsil);
  }
} get_phi_square;

/**
* @brief Cramer's V
*
* @details In statistics, Cramér's V (sometimes referred to as Cramér's phi) is
* a measure of association between two nominal variables, giving a value between
* 0 and +1 (inclusive).
* It is based on Pearson's chi-squared statistic and was published by Harald Cramér in 1946.
*
* ```python
* V = sqrt((phi**2) / (abs(C) - 1)
* ```
*
* @param phi_square Phi-Squared score.
* @param Nclass size of classes array (aka number of classes)
*
* @return The Cramer's V score.
*/
struct // Cramer V
{
  auto operator() (const float & phi_square, const int & Nclass)
  {
    return std::sqrt(phi_square / static_cast<float>(Nclass - 1));
  }
} get_cramer_V;

/**
* @brief Response entropy
*
* @details The entropy of the response distribution.
* The entropy of a distribution is the average negative log probability of outcomes.
*
* ```python
* likelihood_response = TOP/POP
* entropy_response = - sum(likelihood_response * log2(likelihood_response))
* ```
*
* @param TOP array of positive predicted values for each class.
* @param POP array of total samples for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The response entropy score.
*/
struct // Response Entropy
{
  auto operator() (const float * TOP, const float * POP, const int & Nclass)
  {
    return -std :: inner_product(TOP, TOP + Nclass, POP, 0.f, std :: plus < float >(), [](const float & item, const float & pop){float likelihood = item / (pop + epsil); return likelihood * std :: log2(likelihood);});
  }
} get_response_entropy;

/**
* @brief Reference entropy
*
* @details The entropy of the decision problem itself as defined by the counts
* for the reference.
* The entropy of a distribution is the average negative log probability of outcomes.
*
* ```python
* likelihood_reference = P/POP
* entropy_reference = - sum(likelihood_reference * log2(likelihood_reference))
* ```
*
* @param P array of the number of positive samples for each class.
* @param POP array of total samples for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The reference entropy score.
*/
struct // Reference Entropy
{
  auto operator() (const float * P, const float * POP, const int & Nclass)
  {
    return -std :: inner_product(P, P + Nclass, POP, 0.f, std :: plus < float >(), [](const float & item, const float & pop){float likelihood = item / (pop + epsil); return likelihood * std :: log2(likelihood);});
  }
} get_reference_entropy;

/**
* @brief Cross entropy
*
* @details The cross-entropy of the response distribution against the reference distribution.
* The cross-entropy is defined by the negative log probabilities of the response distribution
* weighted by the reference distribution.
*
* ```python
* likelihood_reference = P/POP
* likelihood_response = TOP/POP
* entropy_cross = - sum(likelihood_reference * log2(likelihood_response))
* ```
*
* @param TOP array of positive predicted values for each class.
* @param P array of the number of positive samples for each class.
* @param POP array of total samples for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The cross entropy score.
*/
struct // Cross Entropy
{
  auto operator() (const float * TOP, const float * P, const float * POP, const int & Nclass)
  {
    float res = 0.f;
    for (int i = 0; i < Nclass; ++i)
      res += (P[i] / (POP[i] + epsil)) * std :: log2(TOP[i] / (POP[i] + epsil));
    return -res;
  }
} get_cross_entropy;

/**
* @brief Joint entropy
*
* @details The entropy of the joint reference and response distribution as
* defined by the underlying matrix.
*
* ```python
* P = confusion_matrix / POP
* entropy_joint = - sum(P * log2(P))
* ```
*
* @param confusion_matrix Confusion matrix.
* @param POP array of total samples for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The joint entropy score.
*/
struct // Joint Entropy
{
  auto operator() (const float * confusion_matrix, const float * POP, const int & Nclass)
  {
    float res = 0.f, p_prime;
    for (int i = 0; i < Nclass; ++i)
      for (int j = 0; j < Nclass; ++j)
      {
        p_prime = confusion_matrix[i * Nclass + j] / (POP[i] + epsil);
        res += (p_prime != 0.f) ? p_prime * std :: log2(p_prime) : 0.f;
      }
    return -res;
  }
} get_join_entropy;

/**
* @brief Conditional entropy
*
* @details The entropy of the distribution of categories in the response given that
* the reference category was as specified.
*
* @param confusion_matrix Confusion matrix.
* @param P array of the number of positive samples for each class.
* @param POP array of total samples for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The conditional entropy score.
*/
struct // Conditional Entropy
{
  auto operator() (const float * confusion_matrix, const float * P, const float * POP, const int & Nclass)
  {
    float res = 0.f, p_prime, tmp;
    for (int i = 0; i < Nclass; ++i)
    {
      tmp = 0.f;
      for (int j = 0; j < Nclass; ++j)
      {
        p_prime = confusion_matrix[i * Nclass + j] / (P[i] + epsil);
        tmp += (p_prime != 0.f) ? p_prime * std :: log2(p_prime) : 0.f;
      }
      res += tmp * (P[i] / (POP[i] + epsil));
    }
    return -res;
  }
} get_conditional_entropy;

/**
* @brief Mutual information
*
* @details Mutual information is defined as Kullback-Leibler divergence,
* between the product of the individual distributions and the joint distribution.
* Mutual information is symmetric.
* We could also subtract the conditional entropy of the reference given the response
* from the reference entropy to get the same result.
*
* ```python
* MI = response_entropy - conditional_entropy
* ```
*
* @param response_entropy The response entropy score.
* @param conditional_entropy The conditional entropy score.
*
* @return The mutual information score.
*/
struct // Mutual Information
{
  auto operator() (const float & response_entropy, const float & conditional_entropy)
  {
    return response_entropy - conditional_entropy;
  }
} get_mutual_information;

/**
* @brief Kullback-Leibler divergence
*
* @details In mathematical statistics, the Kullback–Leibler divergence
* (also called relative entropy) is a measure of how one probability distribution
* diverges from a second, expected probability distribution.
*
* ```python
* likelihood_response = TOP/POP
* likelihood_reference = P/POP
* KL = - sum(likelihood_reference * log2(likelihood_reference/likelihood_response))
* ```
*
* @param P array of the number of positive samples for each class.
* @param TOP array of positive predicted values for each class.
* @param POP array of total samples for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The Kullback-Leibler divergence score.
*/
struct // KL Divergence
{
  auto operator() (const float * P, const float * TOP, const float * POP, const int & Nclass)
  {
    float res = 0.f, reference_likelihood;
    for (int i = 0; i < Nclass; ++i)
    {
      reference_likelihood = P[i] / (POP[i] + epsil);
      res += reference_likelihood * std :: log2(reference_likelihood / (TOP[i] / (POP[i] + epsil)));
    }
    return res;
  }
} get_kl_divergence;

/**
* @brief Goodman & Kruskal's lambda B
*
* @details In probability theory and statistics, Goodman & Kruskal's lambda is a
* measure of proportional reduction in error in cross tabulation analysis.
*
* @param confusion_matrix Confusion matrix.
* @param TOP array of positive predicted values for each class.
* @param POP array of total samples for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The lambda B score.
*/
struct // Lambda B
{
  auto operator() (const float * confusion_matrix, const float * TOP, const float * POP, const int & Nclass)
  {
    float maxresponse = -inf;
    float res = 0.f;

    for (int i = 0; i < Nclass; ++i)
    {
      maxresponse = TOP[i] > maxresponse ? TOP[i] : maxresponse;
      res += *std :: max_element(confusion_matrix + i * Nclass, confusion_matrix + i * Nclass + Nclass);
    }

    return (res - maxresponse) / (POP[0] - maxresponse + epsil);
  }
} get_lambda_B;

/**
* @brief Goodman & Kruskal's lambda A
*
* @details In probability theory and statistics, Goodman & Kruskal's lambda is a
* measure of proportional reduction in error in cross tabulation analysis.
*
* @param confusion_matrix Confusion matrix.
* @param P array of the number of positive samples for each class.
* @param POP array of total samples for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The lambda A score.
*/
struct // Lambda A
{
  auto operator() (const float * confusion_matrix, const float * P, const float * POP, const int & Nclass)
  {
    float maxreference = -inf;
    float res = 0.f;

    for (int i = 0; i < Nclass; ++i)
    {
      maxreference = P[i] > maxreference ? P[i] : maxreference;

      float m = -inf;
      for (int j = 0; j < Nclass; ++j)
        m = confusion_matrix[j * Nclass + i] > m ? confusion_matrix[j * Nclass + i] : m;

      res += m;
    }
    return (res - maxreference) / (POP[0] - maxreference + epsil);
  }
} get_lambda_A;

/**
* @brief Chi-squared DF
*
* @details Number of degrees of freedom of this confusion matrix for the chi-squared statistic.
*
* ```python
* DF = (abs(C) - 1)**2
* ```
*
* @param classes array of classes found (this variable is useless in the computation but it is necessary for the graph estimation).
* @param Nclass size of classes array (aka number of classes)
*
* @return The Chi-squared DF score.
*/
struct // Chi-Squared DF
{
  // we need "classes" because the auto-generated code must put this function AFTER the Nclass evalutions
  auto operator() (__unused const float * classes, const int & Nclass)
  {
    return static_cast< float >((Nclass - 1) * (Nclass - 1));
  }
} get_DF;

/**
* @brief Overall Jaccard index
*
* @details
* ```python
* overall_jaccard_index = sum(jaccard_index)
* ```
*
* @param jaccard_index array of Jaccard indexes for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The overall Jaccard index score.
*/
struct // Overall J
{
  auto operator() (const float * jaccard_index, const int & Nclass)
  {
    return std :: accumulate(jaccard_index, jaccard_index + Nclass, 0.f);
  }
} get_overall_jaccard_index;

/**
* @brief Hamming loss
*
* @details The average Hamming loss or Hamming distance between two sets of samples.
*
* ```python
* hamming_loss = 1 / POP * sum(TP)
* ```
*
* @param TP array of true positives for each class.
* @param POP array of total samples for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The overall Hamming loss score.
*/
struct // Hamming loss
{
  auto operator() (const float * TP, const float * POP, const int & Nclass)
  {
    return 1.f / (POP[0] + epsil) * (POP[0] - std :: accumulate(TP, TP + Nclass, 0.f));
  }
} get_hamming_loss;

/**
* @brief Zero-one loss
*
* @details Zero-one loss is a common loss function used with classification learning.
* It assigns 0 to loss for a correct classification and 1 for an incorrect classification.
*
* ```python
* L0 = POP - sum(TP)
* ```
*
* @param TP array of true positives for each class.
* @param POP array of total samples for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The overall Zeor-one loss score.
*/
struct // Zero-one Loss
{
  auto operator() (const float * TP, const float * POP, const int & Nclass)
  {
    return POP[0] - std :: accumulate(TP, TP + Nclass, 0.f);
  }
} get_zero_one_loss;

/**
* @brief No information rate
*
* @details Largest class percentage in the data.
*
* ```python
* NIR = 1/POP max(P)
* ```
*
* @param P array of number of positive samples for each class.
* @param POP array of total samples for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The overall No informative rate score.
*/
struct // NIR
{
  auto operator() (const float * P, const float * POP, const int & Nclass)
  {
    return *std :: max_element(P, P + Nclass) / (POP[0] + epsil);
  }
} get_NIR;

/**
* @brief P-Value
*
* @details In statistical hypothesis testing, the p-value or probability value is,
* for a given statistical model, the probability that, when the null hypothesis is
* true, the statistical summary (such as the absolute value of the sample mean
* difference between two compared groups) would be greater than or equal to the
* actual observed results. Here a one-sided binomial test to see if the accuracy
* is better than the no information rate.
*
* ```python
* x = sum(TP)
* p = NIR
* n = POP
* p_value = 1 - sum([binomial(n, i) * p**i * (1 - p)**(n - i) for i in range(x)])
* ```
*
* @param TP array of number of true positives for each class.
* @param POP array of total samples for each class.
* @param Nclass size of classes array (aka number of classes)
* @param NIR the overall No informative rate score.
*
* @return The p-value score.
*/
struct // P-value
{
  auto operator() (const float * TP, const float * POP, const int & Nclass, const float & NIR)
  {
    float p_value = 0.f;
    const int x = static_cast < int > (std :: accumulate(TP, TP + Nclass, 0.f));

    for (int i = 0; i < x; ++i)
    {
      const int r = i < POP[0] - i ? i : POP[0] - i;

      int numer = 1;

      int iter = POP[0];
      while (iter > POP[0] - r)
      {
        numer *= iter;
        -- iter;
      }

      int denom = 1;

      iter = 1;
      while (iter < r + 1)
      {
        denom *= iter;
        ++ iter;
      }

      const int ncr = numer / (denom + epsil);

      p_value += ncr * std :: pow(NIR, i) * std :: pow(1 - NIR, POP[0] - i);
    }

    return 1.f - p_value;
  }
} get_p_value;

/**
* @brief Overall CEN
*
* @param TOP array of positive predicted values for each class.
* @param P array of number of positive samples for each class.
* @param CEN array of confusion entropies for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The overall CEN score.
*/
struct // Overall CEN
{
  auto operator() (const float * TOP, const float * P, const float * CEN, const int & Nclass)
  {
    float overall_CEN = 0.f;

    const float TOP_sum = std :: accumulate(TOP, TOP + Nclass, 0.f);

    for (int i = 0; i < Nclass; ++i)
    {
      const float up = TOP[i] + P[i];
      const float down = 2.f * TOP_sum;

      overall_CEN += (up / (down + epsil)) * CEN[i];
    }

    return overall_CEN;
  }
} get_overall_CEN;

/**
* @brief Overall MCEN
*
* @param TP array of true positive values for each class.
* @param TOP array of positive predicted values for each class.
* @param P array of number of positive samples for each class.
* @param MCEN array of modified confusion entropies for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The overall MCEN score.
*/
struct // Overall MCEN
{
  auto operator() (const float * TP, const float * TOP, const float * P, const float * MCEN, const int & Nclass)
  {
    float overall_MCEN = 0.f;

    const float alpha = Nclass == 2 ? 0.f : 1.f;

    const float TOP_sum = std :: accumulate(TOP, TOP + Nclass, 0.f);
    const float TP_sum = std :: accumulate(TP, TP + Nclass, 0.f);

    for (int i = 0; i < Nclass; ++i)
    {
      const float up = TOP[i] + P[i] - TP[i];
      const float down = 2.f * TOP_sum - alpha * TP_sum;

      overall_MCEN += (up / (down + epsil)) * MCEN[i];
    }

    return overall_MCEN;
  }
} get_overall_MCEN;

/**
* @brief Overall MCC
*
* @param confusion_matrix Confusion matrix.
* @param TOP array of positive predicted values for each class.
* @param P array of number of positive samples for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The overall MCC score.
*/
struct // Overall MCC
{
  auto operator() (const float * confusion_matrix, const float * TOP, const float * P, const int & Nclass)
  {
    const float s = std :: accumulate(TOP, TOP + Nclass, 0.f);
    float cov_x_y = 0.f;
    float cov_x_x = 0.f;
    float cov_y_y = 0.f;

    for (int i = 0; i < Nclass; ++i)
    {
      cov_x_x += TOP[i] * (s - TOP[i]);
      cov_y_y += P[i] *   (s - P[i]);
      cov_x_y += confusion_matrix[i * Nclass + i] * s - P[i] * TOP[i];
    }

    return cov_x_y / (std :: sqrt(cov_y_y * cov_x_x) + epsil);
  }

} get_overall_MCC;

/**
* @brief Global performance index
*
* @details
* ```python
* RR = 1 / abs(C) * sum(confusion_matrix)
* ```
*
* @param TOP array of positive predicted values for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The RR index score.
*/
struct // RR
{
  auto operator() (const float * TOP, const int & Nclass)
  {
    return std :: accumulate(TOP, TOP + Nclass, 0.f) / Nclass;
  }

} get_RR;

/**
* @brief Class balance accuracy.
*
* @details As an evaluation tool, CBA creates an overall assessment of model
* predictive power by scrutinizing measures simultaneously across each class
* in a conservative manner that guarantees that a model’s ability to recall
* observations from each class and its ability to do so efficiently won’t fall
* below the bound.
*
* @details
* ```python
* CBA = sum(confusion_matrix / max(TOP, P)) / abs(C)
* ```
*
* @param confusion_matrix Confusion matrix.
* @param TOP array of positive predicted values for each class.
* @param P array of number of positive samples for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The CBA score.
*/
struct // CBA
{
  auto operator() (const float * confusion_matrix, const float * TOP, const float * P, const int & Nclass)
  {
    float CBA = 0.f;
    for (int i = 0; i < Nclass; ++i)
      CBA += confusion_matrix[i * Nclass + i] / (std :: max(TOP[i], P[i]) + epsil);
    return CBA / Nclass;
  }

} get_CBA;

/**
* @brief AUNU
*
* @details When dealing with multiclass problems, a global measure of classification
* performances based on the ROC approach (AUNU) has been proposed as the average
* of single-class measures.
*
* ```python
* AUNU = sum(AUC) / abs(C)
* ```
*
* @param AUC array of area under the curve score for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The arrau of AUNU score.
*/
struct // AUNU
{
  auto operator() (const float * AUC, const int & Nclass)
  {
    return std :: accumulate(AUC, AUC + Nclass, 0.f) / Nclass;
  }

} get_AUNU;

/**
* @brief AUNP
*
* @details Another option (AUNP) is that of averaging the AUCi values with
* weights proportional to the number of samples experimentally belonging to each
* class, that is, the a priori class distribution.
*
* ```python
* AUNP = sum(P / POP * AUC)
* ```
*
* @param P array of number of positive samples for each class.
* @param POP array of total samples for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The arrau of AUNP score.
*/
struct // AUNP
{
  auto operator() (const float * P, const float * POP, const float * AUC, const int & Nclass)
  {
    float AUNP = 0.f;
    for (int i = 0; i < Nclass; ++i)
      AUNP += P[i] / (POP[i] * AUC[i] + epsil);
    return AUNP;
  }

} get_AUNP;

/**
* @brief Relative classifier information
*
* @details Performance of different classifiers on the same domain can be
* measured by comparing relative classifier information while classifier
* information (mutual information) can be used for comparison across different
* decision problems.
*
* @param mutual_information array of MI scores for each class.
* @param reference_entropy array of reference entropy scores for each class.
*
* @return The RCI score.
*/
struct // RCI
{
  auto operator() (const float & mutual_information, const float & reference_entropy)
  {
    return mutual_information / (reference_entropy + epsil);
  }
} get_RCI;

/**
* @brief Classification success index
*
* @details The Classification Success Index (CSI) is an overall measure defined
* by averaging ICSI over all classes.
*
* ```python
* CSI = 1 / abs(C) * sum(ICSI)
* ```
*
* @param ICIS array of individual classification success indexes for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return
*/
struct // CSI
{
  auto operator() (const float * ICSI, const int & Nclass)
  {
    return std :: accumulate(ICSI, ICSI + Nclass, 0.f) / Nclass;
  }
} get_CSI;

/**
* @brief Pearson's C
*
* @details The contingency coefficient is a coefficient of association that
* tells whether two variables or data sets are independent or dependent of/on
* each other.
* It is also known as Pearson’s coefficient (not to be confused with Pearson’s
* coefficient of skewness).
*
* ```python
* C = sqrt(chi**2 / (chi**2 + POP))
* ```
*
* @param chi_square Chi-squared score.
* @param POP array of total samples for each class.
*
* @return The Pearson's C score.
*/
struct // Pearson C
{
  auto operator() (const float & chi_square, const float * POP)
  {
    return std :: sqrt (chi_square / (POP[0] + chi_square + epsil));
  }

} get_overall_pearson_C;


/**
* @brief Utility function for micro score evaluation (it is valid for TPR micro, PPV micro, F1 micro)
*
* @details The function computes the score according to the formula:
*
* ```python
* res = sum(TP) / (sum(TP) + sum(FN))
* ```
*
* @param TP array of true positives for each class.
* @param FN array of false negatives for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return The required score.
*/
struct // TPR Micro, PPV Micro, F1 Micro
{
  auto operator() (const float * TP, const float * FN, const int & Nclass)
  {
    const float TP_sum = std :: accumulate(TP, TP + Nclass, 0.f);
    const float FN_sum = std :: accumulate(FN, FN + Nclass, 0.f);
    return TP_sum / (TP_sum + FN_sum + epsil);
  }
} get_TPR_PPV_F1_micro;

/**
* @brief Matthews's benchmark
*
* @details MCC is a confusion matrix method of calculating the Pearson product-moment
* correlation coefficient (not to be confused with Pearson's C).
* Therefore, it has the same interpretation.
* The score follows the ranges
* - SOA6 < 0.3 Negligible
* - 0.3 < SOA6 < 0.5 Weak
* - 0.5 < SOA6 < 0.7 Moderate
* - 0.7 < SOA6 < 0.9 Strong
* - 0.9 < SOA6 < 1.0 Very strong
*
* @param overall_MCC Overall Matthews correlation coefficient.
*
* @return The value of SOA6 score.
*/
struct // SOA6(Matthews)
{
  auto operator() (const float & overall_MCC)
  {
    return std :: isnan(overall_MCC) || std :: isinf(overall_MCC) ? -1.f : overall_MCC < .3f ? 0.f : overall_MCC >= .3f && overall_MCC < .5f ? 1.f : overall_MCC >= .5f && overall_MCC < .7f ? 2.f : overall_MCC >= .7f && overall_MCC < .9f ? 3.f : 4.f;
  }

} get_MCC_analysis;

/**
* @brief Cicchetti's benchmark
*
* @details The score follows the ranges
* - SOA4 < 0.4 Poor
* - 0.4  < SOA4 < 0.6 Fair
* - 0.6  < SOA4 < 0.75 Good
* - 0.75 < SOA4 < 1.0 Excellent
*
* @param overall_kappa Overall Kappa score.
*
* @return The value of SOA4 score.
*/
struct // SOA4(Cicchetti)
{
  auto operator() (const float & overall_kappa)
  {
    return std :: isnan(overall_kappa) || std :: isinf(overall_kappa) ? -1.f : overall_kappa < .4f ? 0.f : overall_kappa >= .4f && overall_kappa < .59f ? 1.f : overall_kappa >= .59f && overall_kappa < .74f ? 2.f : overall_kappa >= .74f && overall_kappa < 1.f ? 3.f : 0.f;
  }

} get_kappa_analysis_cicchetti;

/**
* @brief Landis & Koch's benchmark
*
* @details The score follows the ranges
* - SOA1 < 0 Poor
* - 0   < SOA1 < 0.2 Slight
* - 0.2 < SOA1 < 0.4 Fair
* - 0.4 < SOA1 < 0.6 Moderate
* - 0.6 < SOA1 < 0.8 substantial
* - 0.8 < SOA1 < 1.0 Almost perfect
*
* @param overall_kappa Overall Kappa score.
*
* @return The value of SOA1 score.
*/
struct // SOA1(Landis & Koch)
{
  auto operator() (const float & overall_kappa)
  {
    return std :: isnan(overall_kappa) || std :: isinf(overall_kappa) ? -1.f : overall_kappa < .0f ? 0.f : overall_kappa >= .0f && overall_kappa < .2f ? 1.f : overall_kappa >= .2f && overall_kappa < .4f ? 2.f : overall_kappa >= .4f && overall_kappa < 6.f ? 3.f : overall_kappa >= .6f && overall_kappa < .8f ? 4.f : overall_kappa >= .8f && overall_kappa <= 1.f ? 5.f : 0.f;
  }

} get_kappa_analysis_koch;

/**
* @brief Fleiss' benchmark
*
* @details The score follows the ranges
* - SOA2 < 0.4 Poor
* - 0.4 < SOA2 < 0.75 Intermediate to Good
* - SOA2 > 0.75 Excellent
*
* @param overall_kappa Overall Kappa score.
*
* @return The value of SOA2 score.
*/
struct // SOA2(Fleiss)
{
  auto operator() (const float & overall_kappa)
  {
    return std :: isnan(overall_kappa) || std :: isinf(overall_kappa) ? -1.f : overall_kappa < .4f ? 0.f : overall_kappa >= .4f && overall_kappa < .75f ? 1.f : overall_kappa >= .75f ? 2.f : 0.f;
  }

} get_kappa_analysis_fleiss;

/**
* @brief Altman's benchmark
*
* @details The score follows the ranges
* - SOA3 < 0.2 Poor
* - 0.2 < SOA3 < 0.4 Fair
* - 0.4 < SOA3 < 0.6 Moderate
* - 0.6 < SOA3 < 0.8 Good
* - 0.8 < SOA3 < 1.0 Very good
*
* @param overall_kappa Overall Kappa score.
*
* @return The value of SOA3 score.
*/
struct // SOA3(Altman)
{
  auto operator() (const float & overall_kappa)
  {
    return std :: isnan(overall_kappa) || std :: isinf(overall_kappa) ? -1.f : overall_kappa < .2f ? 0.f : overall_kappa >= .2f && overall_kappa < .4f ? 1.f : overall_kappa >= .4f && overall_kappa < .6f ? 2.f : overall_kappa >= .6f && overall_kappa < .8f ? 3.f : overall_kappa >= .8f && overall_kappa <= 1.f ? 4.f : 0.f;
  }

} get_kappa_analysis_altman;

/**
* @brief Cramer's benchmark
*
* @details The score follows the ranges
* - SOA5 < 0.1 Negligible
* - 0.1 < SOA5 < 0.2 Weak
* - 0.2 < SOA5 < 0.4 Moderate
* - 0.4 < SOA5 < 0.6 Relatively Strong
* - 0.6 < SOA5 < 0.8 Strong
* - 0.8 < SOA5 < 1.0 Very strong
*
* @param cramer_V Overall Cramer's V score.
*
* @return The value of SOA5 score.
*/
struct // SOA5(Cramer)
{
  auto operator() (const float & cramer_V)
  {
    return cramer_V < .1f ? 0.f : cramer_V >= .1f && cramer_V < .2f ? 1.f : cramer_V >= .2f && cramer_V < .4f ? 2.f : cramer_V >= .4f && cramer_V < .6f ? 3.f : cramer_V >= .6f && cramer_V < .8f ? 4.f : 5.f;
  }

} get_V_analysis;

/**
* @brief TPR_Macro
*
* @details
* ```python
* TPR_macro = 1/abs(C) * sum(TP / (TP + FN))
* ```
*
* @param TPR array of true positive rates for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return the TPR macro score.
*/
struct // TPR Macro
{
  auto operator() (const float * TPR, const int & Nclass)
  {
    return std :: accumulate(TPR, TPR + Nclass, 0.f) / Nclass;
  }
} get_TPR_macro;

/**
* @brief PPV_Macro
*
* @details
* ```python
* PPV_macro = 1/abs(C) * sum(TP / (TP + FN))
* ```
*
* @param PPV array of true positive predicted values for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return the PPV macro score.
*/
struct // PPV Macro
{
  auto operator() (const float * PPV, const int & Nclass)
  {
    return std :: accumulate(PPV, PPV + Nclass, 0.f) / Nclass;
  }
} get_PPV_macro;

/**
* @brief ACC_Macro
*
* @details
* ```python
* ACC_macro = 1/abs(C) * sum(ACC)
* ```
*
* @param ACC array of accuracies for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return the ACC macro score.
*/
struct // ACC Macro
{
  auto operator() (const float * ACC, const int & Nclass)
  {
    return std :: accumulate(ACC, ACC + Nclass, 0.f) / Nclass;
  }
} get_ACC_macro;

/**
* @brief F1_Macro
*
* @details
* ```python
* F1_macro = 2/abs(C) * sum((TPR * PPV) / (TPR + PPV))
* ```
*
* @param F1_score array of F1 scores for each class.
* @param Nclass size of classes array (aka number of classes)
*
* @return the F1 macro score.
*/
struct // F1 Macro
{
  auto operator() (const float * F1_SCORE, const int & Nclass)
  {
    return std :: accumulate(F1_SCORE, F1_SCORE + Nclass, 0.f) / Nclass;
  }
} get_F1_macro;



#endif // __overall_stats_h__
