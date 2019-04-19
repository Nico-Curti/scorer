#ifndef OVERALL_STATS_H
#define OVERALL_STATS_H

#include <common_stats.h>

#ifdef _MSC_VER
  #ifndef __unused
  #define __unused
  #endif
#else
  #ifndef __unused
  #define __unused __attribute__((__unused__))
  #endif
#endif

struct
{
  auto operator()(const float *TP, const float *POP, const int &Nclass)
  {
    return std::accumulate(TP, TP + Nclass, 0.f) / POP[0];
  }
} get_overall_accuracy;

struct
{
  auto operator()(const float *RACCU, const int &Nclass)
  {
    return std::accumulate(RACCU, RACCU + Nclass, 0.f);
  }
} get_overall_random_accuracy_unbiased;

struct
{
  auto operator()(const float *RACC, const int &Nclass)
  {
    return std::accumulate(RACC, RACC + Nclass, 0.f);
  }
} get_overall_random_accuracy;

struct
{
  auto operator()(const float &overall_random_accuracy, const float &overall_accuracy)
  {
    return (overall_accuracy - overall_random_accuracy) / (1.f - overall_random_accuracy);
  }
} get_overall_kappa;

struct
{
  auto operator()(const float *P, const float *TOP, const float *POP, const int &Nclass)
  {
    float res = 0.f;
    for (int i = 0; i < Nclass; ++i)
      res += ( (P[i] + TOP[i])*(P[i] + TOP[i]) ) / ( 4.f * POP[i] * POP[i] );
    return res;
  }
} get_PC_PI;

struct
{
  auto operator()(const float *P, const float *TOP, const float *POP, const int &Nclass)
  {
    float res = 0.f, pi;
    for (int i = 0; i < Nclass; ++i)
    {
      pi = (P[i] + TOP[i]) / (2.f * POP[i]);
      res += pi * (1.f - pi);
    }
    return res / static_cast<float>(Nclass - 1);
  }
} get_PC_AC1;

struct
{
  auto operator()(__unused const float *classes, const int &Nclass)
  {
    return 1.f / static_cast<float>(Nclass);
  }
} get_PC_S;

struct
{
  auto operator()(const float &PC_PI, const float &overall_accuracy)
  {
    return (overall_accuracy - PC_PI) / (1.f - PC_PI);
  }
} get_PI;

struct
{
  auto operator()(const float &PC_AC1, const float &overall_accuracy)
  {
    return (overall_accuracy - PC_AC1) / (1.f - PC_AC1);
  }
} get_AC1;

struct
{
  auto operator()(const float &PC_S, const float &overall_accuracy)
  {
    return (overall_accuracy - PC_S) / (1.f - PC_S);
  }
} get_S;

struct
{
  auto operator()(const float &overall_accuracy, const float &overall_random_accuracy, const float *POP, __unused const int &Nclass)
  {
    return std::sqrt( (overall_accuracy * (1.f - overall_accuracy) ) / (POP[0] * (1.f - overall_random_accuracy)*(1.f - overall_random_accuracy)) );
  }
} get_kappa_SE;

struct
{
  auto operator()(const float &overall_random_accuracy_unbiased, const float &overall_accuracy)
  {
    return (overall_accuracy - overall_random_accuracy_unbiased) / (1.f - overall_random_accuracy_unbiased);
  }
} get_kappa_unbiased;

struct
{
  auto operator()(const float &overall_accuracy)
  {
    return 2.f * overall_accuracy - 1.f;
  }
} get_kappa_no_prevalence;

struct
{
  auto operator()(__unused const float &overall_kappa, __unused const float &kappa_SE)
  {
    float kappa_CI = 0.f;
    // MISS
    return kappa_CI;
  }
} get_kappa_CI;

struct
{
  auto operator()(const float &overall_accuracy, const float *POP, __unused const int &Nclass)
  {
    return std::sqrt( (overall_accuracy * (1.f - overall_accuracy)) / POP[0]);
  }
} get_overall_accuracy_se;

struct
{
  auto operator()(__unused const float *classes, const float *confusion_matrix, const float *TOP, const float *P, const float *POP, const int &Nclass)
  {
    float res = 0.f,
          expected;
    for (int i = 0; i < Nclass; ++i)
      for (int j = 0; j < Nclass; ++j)
      {
        expected = (TOP[j] * P[i]) / POP[i];
        res += (confusion_matrix[i*Nclass + j] - expected) * (confusion_matrix[i*Nclass + j] - expected) / expected;
      }
    return res;
  }
} get_chi_square;

struct
{
  auto operator()(const float &chi_square, const float *POP, __unused const float &Nclass)
  {
    return chi_square / POP[0];
  }
} get_phi_square;

struct
{
  auto operator()(const float &phi_square, __unused const float *classes, const int &Nclass)
  {
    return std::sqrt(phi_square / static_cast<float>(Nclass - 1));
  }
} get_cramers_V_calc;

struct
{
  auto operator()(const float *TOP, const float *POP, const int &Nclass)
  {
    return -std::inner_product(TOP, TOP + Nclass, POP, 0.f, std::plus<float>(), [](const float &item, const float &pop){float likelihood = item / pop; return likelihood * std::log2(likelihood);});
  }
} get_response_entropy;

struct
{
  auto operator()(const float *P, const float *POP, const int &Nclass)
  {
    return -std::inner_product(P, P + Nclass, POP, 0.f, std::plus<float>(), [](const float &item, const float &pop){float likelihood = item / pop; return likelihood * std::log2(likelihood);});
  }
} get_reference_entropy;

struct
{
  auto operator()(const float *TOP, const float *P, const float *POP, const int &Nclass)
  {
    float res = 0.f;
    for (int i = 0; i < Nclass; ++i)
      res += (P[i] / POP[i]) * std::log2(TOP[i] / POP[i]);
    return -res;
  }
} get_cross_entropy;

struct
{
  auto operator()(__unused const float *classes, const float *confusion_matrix, const float *POP, const int &Nclass)
  {
    float res = 0.f, p_prime;
    for (int i = 0; i < Nclass; ++i)
      for (int j = 0; j < Nclass; ++j)
      {
        p_prime = confusion_matrix[i*Nclass + j] / POP[i];
        res += (p_prime != 0.f) ? p_prime * std::log2(p_prime) : 0.f;
      }
    return -res;
  }
} get_join_entropy;

struct
{
  auto operator()(__unused const float *classes, const float *confusion_matrix, const float *P, const float *POP, const int &Nclass)
  {
    float res = 0.f, p_prime, tmp;
    for (int i = 0; i < Nclass; ++i)
    {
      tmp = 0.f;
      for (int j = 0; j < Nclass; ++j)
      {
        p_prime = confusion_matrix[i*Nclass + j] / P[i];
        tmp += (p_prime != 0.f) ? p_prime * std::log2(p_prime) : 0.f;
      }
      res += tmp * (P[i] / POP[i]);
    }
    return -res;
  }
} get_conditional_entropy;

struct
{
  auto operator()(const float &response_entropy, const float &conditional_entropy)
  {
    return response_entropy - conditional_entropy;
  }
} get_mutual_information;

struct
{
  auto operator()(const float *P, const float *TOP, const float *POP, const int &Nclass)
  {
    float res = 0.f, reference_likelihood;
    for (int i = 0; i < Nclass; ++i)
    {
      reference_likelihood = P[i] / POP[i];
      res += reference_likelihood * std::log2(reference_likelihood / (TOP[i] / POP[i]));
    }
    return res;
  }
} get_kl_divergence;

struct
{
  auto operator()(__unused const float *classes, __unused const float *confusion_matrix, __unused const float *TOP, __unused const float *POP, __unused const int &Nclass)
  {
    float maxresponse = -inf,
          res = 0.f;
          // MISS
    return (res - maxresponse) / (POP[0] - maxresponse);
  }
} get_lambda_B;

struct
{
  auto operator()(__unused const float *classes, __unused const float *confusion_matrix, __unused const float *P, __unused const float *POP, __unused const int &Nclass)
  {
    float maxreference = -inf,
          res = 0.f;
          // MISS
    return (res - maxreference) / (POP[0] - maxreference);
  }
} get_lambda_A;

struct
{
  auto operator()(__unused const float *classes, const int &Nclass)
  {
    return static_cast<float>((Nclass - 1)*(Nclass - 1));
  }
} get_DF;

struct
{
  auto operator()(const float *jaccard_index, const int &Nclass)
  {
    // MISS return (sum, mean)
    return std::accumulate(jaccard_index, jaccard_index + Nclass, 0.f) / Nclass;
  }
} get_overall_jaccard_index;

struct
{
  auto operator()(const float *TP, const float *POP, const int &Nclass)
  {
    return 1.f / POP[0] * (POP[0] - std::accumulate(TP, TP + Nclass, 0.f));
  }
} get_hamming_loss;

struct
{
  auto operator()(const float *TP, const float *POP, const int &Nclass)
  {
    return POP[0] - std::accumulate(TP, TP + Nclass, 0.f);
  }
} get_zero_one_loss;

struct
{
  auto operator()(const float *P, const float *POP, const int &Nclass)
  {
    return *std::max_element(P, P + Nclass) / POP[0];
  }
} get_NIR;

struct
{
  auto operator()(__unused const float *TP, __unused const float *POP, __unused const int &Nclass, __unused const float &NIR)
  {
    float p_value = 0.f;
    // MISS
    return p_value;
  }
} get_p_value;

struct
{
  auto operator()(__unused const float *classes, __unused const float *confusion_matrix, __unused const float *CEN, __unused const int &Nclass)
  {
    float overall_CEN = 0.f;
    // MISS
    return overall_CEN;
  }
} get_overall_CEN;

struct
{
  auto operator()(__unused const float *classes, __unused const float *confusion_matrix, __unused const float *MCEN, __unused const int &Nclass)
  {
    float overall_MCEN = 0.f;
    // MISS
    return overall_MCEN;
  }
} get_overall_MCEN;


#endif // OVERALL_STATS_H
