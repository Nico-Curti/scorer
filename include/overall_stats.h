#ifndef __overall_stats_h__
#define __overall_stats_h__

#include <common_stats.h>

#ifdef _MSC_VER

  #ifndef __unused
    #define __unused
  #endif

#else // Not Visual Studio Compiler

  #ifndef __unused
    #define __unused __attribute__((__unused__))
  #endif

#endif

struct // Overall ACC
{
  auto operator() (const float * TP, const float * POP, const int & Nclass)
  {
    return std :: accumulate(TP, TP + Nclass, 0.f) / POP[0];
  }
} get_overall_accuracy;

struct // Overall RACCU
{
  auto operator() (const float * RACCU, const int & Nclass)
  {
    return std :: accumulate(RACCU, RACCU + Nclass, 0.f);
  }
} get_overall_random_accuracy_unbiased;

struct // Overall RACC
{
  auto operator() (const float * RACC, const int & Nclass)
  {
    return std :: accumulate(RACC, RACC + Nclass, 0.f);
  }
} get_overall_random_accuracy;

struct // Kappa
{
  auto operator() (const float & overall_random_accuracy, const float & overall_accuracy)
  {
    return (overall_accuracy - overall_random_accuracy) / (1.f - overall_random_accuracy);
  }
} get_overall_kappa;

struct // PC_PI
{
  auto operator() (const float * P, const float * TOP, const float * POP, const int & Nclass)
  {
    float res = 0.f;
    for (int i = 0; i < Nclass; ++i)
      res += ( (P[i] + TOP[i]) * (P[i] + TOP[i]) ) / ( 4.f * POP[i] * POP[i] );
    return res;
  }
} get_PC_PI;

struct // PC_AC1
{
  auto operator() (const float * P, const float * TOP, const float * POP, const int & Nclass)
  {
    float AC1 = 0.f;
    for (int i = 0; i < Nclass; ++i)
    {
      const float pi = (P[i] + TOP[i]) / (2.f * POP[i]);
      AC1 += pi * (1.f - pi);
    }
    return AC1 / (Nclass - 1);
  }
} get_PC_AC1;

struct // PC_S
{
  // we need "classes" because the auto-generated code must put this function AFTER the Nclass evalution
  auto operator() (__unused const float * classes, const int & Nclass)
  {
    return 1.f / static_cast < float >(Nclass);
  }
} get_PC_S;

struct // Scott PI
{
  auto operator() (const float & PC_PI, const float & overall_accuracy)
  {
    return (overall_accuracy - PC_PI) / (1.f - PC_PI);
  }
} get_PI;

struct // Get AC1
{
  auto operator() (const float & PC_AC1, const float & overall_accuracy)
  {
    return (overall_accuracy - PC_AC1) / (1.f - PC_AC1);
  }
} get_AC1;

struct // Bennett S
{
  auto operator() (const float & PC_S, const float & overall_accuracy)
  {
    return (overall_accuracy - PC_S) / (1.f - PC_S);
  }
} get_S;

struct // Kappa Standard Error
{
  auto operator() (const float & overall_accuracy, const float & overall_random_accuracy, const float * POP)
  {
    return std :: sqrt( (overall_accuracy * (1.f - overall_accuracy) ) / (POP[0] * (1.f - overall_random_accuracy)*(1.f - overall_random_accuracy)) );
  }
} get_kappa_SE;

struct // Kappa Unbiased
{
  auto operator() (const float & overall_random_accuracy_unbiased, const float & overall_accuracy)
  {
    return (overall_accuracy - overall_random_accuracy_unbiased) / (1.f - overall_random_accuracy_unbiased);
  }
} get_kappa_unbiased;

struct // Kappa No Prevalence
{
  auto operator() (const float & overall_accuracy)
  {
    return 2.f * overall_accuracy - 1.f;
  }
} get_kappa_no_prevalence;

struct // Kappa 95% CI up
{
  auto operator() (const float & overall_kappa, const float & kappa_SE)
  {
    return overall_kappa + 1.96 * kappa_SE;
  }
} get_kappa_CI_up;

struct // Kappa 95% CI down
{
  auto operator() (const float & overall_kappa, const float & kappa_SE)
  {
    return overall_kappa - 1.96 * kappa_SE;
  }
} get_kappa_CI_down;

struct // Standard Error
{
  auto operator() (const float & overall_accuracy, const float * POP)
  {
    return std :: sqrt( (overall_accuracy * (1.f - overall_accuracy)) / POP[0]);
  }
} get_overall_accuracy_se;

struct // 95% CI up
{
  auto operator() (const float & overall_accuracy, const float & overall_accuracy_se)
  {
    return overall_accuracy + 1.96f * overall_accuracy_se;
  }
} get_overall_accuracy_ci_up;

struct // 95% CI down
{
  auto operator() (const float & overall_accuracy, const float & overall_accuracy_se)
  {
    return overall_accuracy - 1.96f * overall_accuracy_se;
  }
} get_overall_accuracy_ci_down;

struct // Chi-Squared
{
  auto operator() (const float * confusion_matrix, const float * TOP, const float * P, const float * POP, const int & Nclass)
  {
    float res = 0.f,
          expected;
    for (int i = 0; i < Nclass; ++i)
      for (int j = 0; j < Nclass; ++j)
      {
        expected = (TOP[j] * P[i]) / POP[i];
        res += (confusion_matrix[i * Nclass + j] - expected) * (confusion_matrix[i * Nclass + j] - expected) / expected;
      }
    return res;
  }
} get_chi_square;

struct // Phi-Squared
{
  auto operator() (const float & chi_square, const float * POP)
  {
    return chi_square / POP[0];
  }
} get_phi_square;

struct // Cramer V
{
  auto operator() (const float & phi_square, const int & Nclass)
  {
    return std::sqrt(phi_square / static_cast<float>(Nclass - 1));
  }
} get_cramer_V;

struct // Response Entropy
{
  auto operator() (const float * TOP, const float * POP, const int & Nclass)
  {
    return -std :: inner_product(TOP, TOP + Nclass, POP, 0.f, std :: plus < float >(), [](const float & item, const float & pop){float likelihood = item / pop; return likelihood * std :: log2(likelihood);});
  }
} get_response_entropy;

struct // Reference Entropy
{
  auto operator() (const float * P, const float * POP, const int & Nclass)
  {
    return -std :: inner_product(P, P + Nclass, POP, 0.f, std :: plus < float >(), [](const float & item, const float & pop){float likelihood = item / pop; return likelihood * std :: log2(likelihood);});
  }
} get_reference_entropy;

struct // Cross Entropy
{
  auto operator() (const float * TOP, const float * P, const float * POP, const int & Nclass)
  {
    float res = 0.f;
    for (int i = 0; i < Nclass; ++i)
      res += (P[i] / POP[i]) * std :: log2(TOP[i] / POP[i]);
    return -res;
  }
} get_cross_entropy;

struct // Joint Entropy
{
  auto operator() (const float * confusion_matrix, const float * POP, const int & Nclass)
  {
    float res = 0.f, p_prime;
    for (int i = 0; i < Nclass; ++i)
      for (int j = 0; j < Nclass; ++j)
      {
        p_prime = confusion_matrix[i * Nclass + j] / POP[i];
        res += (p_prime != 0.f) ? p_prime * std :: log2(p_prime) : 0.f;
      }
    return -res;
  }
} get_join_entropy;

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
        p_prime = confusion_matrix[i * Nclass + j] / P[i];
        tmp += (p_prime != 0.f) ? p_prime * std :: log2(p_prime) : 0.f;
      }
      res += tmp * (P[i] / POP[i]);
    }
    return -res;
  }
} get_conditional_entropy;

struct // Mutual Information
{
  auto operator() (const float & response_entropy, const float & conditional_entropy)
  {
    return response_entropy - conditional_entropy;
  }
} get_mutual_information;

struct // KL Divergence
{
  auto operator() (const float * P, const float * TOP, const float * POP, const int & Nclass)
  {
    float res = 0.f, reference_likelihood;
    for (int i = 0; i < Nclass; ++i)
    {
      reference_likelihood = P[i] / POP[i];
      res += reference_likelihood * std :: log2(reference_likelihood / (TOP[i] / POP[i]));
    }
    return res;
  }
} get_kl_divergence;

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

    return (res - maxresponse) / (POP[0] - maxresponse);
  }
} get_lambda_B;

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
    return (res - maxreference) / (POP[0] - maxreference);
  }
} get_lambda_A;

struct // Chi-Squared DF
{
  // we need "classes" because the auto-generated code must put this function AFTER the Nclass evalutions
  auto operator() (__unused const float * classes, const int & Nclass)
  {
    return static_cast< float >((Nclass - 1) * (Nclass - 1));
  }
} get_DF;

struct // Overall J
{
  auto operator() (const float * jaccard_index, const int & Nclass)
  {
    return std :: accumulate(jaccard_index, jaccard_index + Nclass, 0.f);
  }
} get_overall_jaccard_index;

struct // Hamming loss
{
  auto operator() (const float * TP, const float * POP, const int & Nclass)
  {
    return 1.f / POP[0] * (POP[0] - std :: accumulate(TP, TP + Nclass, 0.f));
  }
} get_hamming_loss;

struct // Zero-one Loss
{
  auto operator() (const float * TP, const float * POP, const int & Nclass)
  {
    return POP[0] - std :: accumulate(TP, TP + Nclass, 0.f);
  }
} get_zero_one_loss;

struct // NIR
{
  auto operator() (const float * P, const float * POP, const int & Nclass)
  {
    return *std :: max_element(P, P + Nclass) / POP[0];
  }
} get_NIR;

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

      const int ncr = numer / denom;

      p_value += ncr * std :: pow(NIR, i) * std :: pow(1 - NIR, POP[0] - i);
    }

    return 1.f - p_value;
  }
} get_p_value;

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

      overall_CEN += (up / down) * CEN[i];
    }

    return overall_CEN;
  }
} get_overall_CEN;

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

      overall_MCEN += (up / down) * MCEN[i];
    }

    return overall_MCEN;
  }
} get_overall_MCEN;

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

    return cov_x_y / std :: sqrt(cov_y_y * cov_x_x);
  }

} get_overall_MCC;

struct // RR
{
  auto operator() (const float * TOP, const int & Nclass)
  {
    return std :: accumulate(TOP, TOP + Nclass, 0.f) / Nclass;
  }

} get_RR;

struct // CBA
{
  auto operator() (const float * confusion_matrix, const float * TOP, const float * P, const int & Nclass)
  {
    float CBA = 0.f;
    for (int i = 0; i < Nclass; ++i)
      CBA += confusion_matrix[i * Nclass + i] / std :: max(TOP[i], P[i]);
    return CBA / Nclass;
  }

} get_CBA;

struct // AUNU
{
  auto operator() (const float * AUC, const int & Nclass)
  {
    return std :: accumulate(AUC, AUC + Nclass, 0.f) / Nclass;
  }

} get_AUNU;

struct // AUNP
{
  auto operator() (const float * P, const float * POP, const float * AUC, const int & Nclass)
  {
    float AUNP = 0.f;
    for (int i = 0; i < Nclass; ++i)
      AUNP += P[i] / POP[i] * AUC[i];
    return AUNP;
  }

} get_AUNP;

struct // RCI
{
  auto operator() (const float & mutual_information, const float & reference_entropy)
  {
    return mutual_information / reference_entropy;
  }
} get_RCI;

struct // CSI
{
  auto operator() (const float * ICSI, const int & Nclass)
  {
    return std :: accumulate(ICSI, ICSI + Nclass, 0.f) / Nclass;
  }
} get_CSI;

struct // Pearson C
{
  auto operator() (const float & chi_square, const float * POP)
  {
    return std :: sqrt (chi_square / (POP[0] + chi_square));
  }

} get_overall_pearson_C;


struct // TPR Micro, PPV Micro, F1 Micro
{
  auto operator() (const float * TP, const float * FN, const int & Nclass)
  {
    const float TP_sum = std :: accumulate(TP, TP + Nclass, 0.f);
    const float FN_sum = std :: accumulate(FN, FN + Nclass, 0.f);
    return TP_sum / (TP_sum + FN_sum);
  }
} get_TPR_PPV_F1_micro;

struct // SOA6(Matthews)
{
  auto operator() (const float & overall_MCC)
  {
    return std :: isnan(overall_MCC) || std :: isinf(overall_MCC) ? -1.f : overall_MCC < .3f ? 0.f : overall_MCC >= .3f && overall_MCC < .5f ? 1.f : overall_MCC >= .5f && overall_MCC < .7f ? 2.f : overall_MCC >= .7f && overall_MCC < .9f ? 3.f : 4.f;
  }

} get_MCC_analysis;

struct // SOA4(Cicchetti)
{
  auto operator() (const float & overall_kappa)
  {
    return std :: isnan(overall_kappa) || std :: isinf(overall_kappa) ? -1.f : overall_kappa < .4f ? 0.f : overall_kappa >= .4f && overall_kappa < .59f ? 1.f : overall_kappa >= .59f && overall_kappa < .74f ? 2.f : overall_kappa >= .74f && overall_kappa < 1.f ? 3.f : 0.f;
  }

} get_kappa_analysis_cicchetti;

struct // SOA1(Landis & Koch)
{
  auto operator() (const float & overall_kappa)
  {
    return std :: isnan(overall_kappa) || std :: isinf(overall_kappa) ? -1.f : overall_kappa < .0f ? 0.f : overall_kappa >= .0f && overall_kappa < .2f ? 1.f : overall_kappa >= .2f && overall_kappa < .4f ? 2.f : overall_kappa >= .4f && overall_kappa < 6.f ? 3.f : overall_kappa >= .6f && overall_kappa < .8f ? 4.f : overall_kappa >= .8f && overall_kappa <= 1.f ? 5.f : 0.f;
  }

} get_kappa_analysis_koch;

struct // SOA2(Fleiss)
{
  auto operator() (const float & overall_kappa)
  {
    return std :: isnan(overall_kappa) || std :: isinf(overall_kappa) ? -1.f : overall_kappa < .4f ? 0.f : overall_kappa >= .4f && overall_kappa < .75f ? 1.f : overall_kappa >= .75f ? 2.f : 0.f;
  }

} get_kappa_analysis_fleiss;

struct // SOA3(Altman)
{
  auto operator() (const float & overall_kappa)
  {
    return std :: isnan(overall_kappa) || std :: isinf(overall_kappa) ? -1.f : overall_kappa < .2f ? 0.f : overall_kappa >= .2f && overall_kappa < .4f ? 1.f : overall_kappa >= .4f && overall_kappa < .6f ? 2.f : overall_kappa >= .6f && overall_kappa < .8f ? 3.f : overall_kappa >= .8f && overall_kappa <= 1.f ? 4.f : 0.f;
  }

} get_kappa_analysis_altman;

struct // SOA5(Cramer)
{
  auto operator() (const float & cramer_V)
  {
    return cramer_V < .1f ? 0.f : cramer_V >= .1f && cramer_V < .2f ? 1.f : cramer_V >= .2f && cramer_V < .4f ? 2.f : cramer_V >= .4f && cramer_V < .6f ? 3.f : cramer_V >= .6f && cramer_V < .8f ? 4.f : 5.f;
  }

} get_V_analysis;

struct // TPR Macro
{
  auto operator() (const float * TPR, const int & Nclass)
  {
    return std :: accumulate(TPR, TPR + Nclass, 0.f) / Nclass;
  }
} get_TPR_macro;

struct // PPV Macro
{
  auto operator() (const float * PPV, const int & Nclass)
  {
    return std :: accumulate(PPV, PPV + Nclass, 0.f) / Nclass;
  }
} get_PPV_macro;

struct // ACC Macro
{
  auto operator() (const float * ACC, const int & Nclass)
  {
    return std :: accumulate(ACC, ACC + Nclass, 0.f) / Nclass;
  }
} get_ACC_macro;

struct // F1 Macro
{
  auto operator() (const float * F1_SCORE, const int & Nclass)
  {
    return std :: accumulate(F1_SCORE, F1_SCORE + Nclass, 0.f) / Nclass;
  }
} get_F1_macro;



#endif // __overall_stats_h__
