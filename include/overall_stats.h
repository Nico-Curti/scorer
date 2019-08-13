#ifndef __overall_stats_h__
#define __overall_stats_h__

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
  auto operator() (const float * TP, const float * POP, const int & Nclass)
  {
    return std :: accumulate(TP, TP + Nclass, 0.f) / POP[0];
  }
} get_overall_accuracy;

struct
{
  auto operator() (const float * RACCU, const int & Nclass)
  {
    return std :: accumulate(RACCU, RACCU + Nclass, 0.f);
  }
} get_overall_random_accuracy_unbiased;

struct
{
  auto operator() (const float * RACC, const int & Nclass)
  {
    return std :: accumulate(RACC, RACC + Nclass, 0.f);
  }
} get_overall_random_accuracy;

struct
{
  auto operator() (const float & overall_random_accuracy, const float & overall_accuracy)
  {
    return (overall_accuracy - overall_random_accuracy) / (1.f - overall_random_accuracy);
  }
} get_overall_kappa;

struct
{
  auto operator() (const float * P, const float * TOP, const float * POP, const int & Nclass)
  {
    float res = 0.f;
    for (int i = 0; i < Nclass; ++i)
      res += ( (P[i] + TOP[i]) * (P[i] + TOP[i]) ) / ( 4.f * POP[i] * POP[i] );
    return res;
  }
} get_PC_PI;

struct
{
  auto operator() (const float * P, const float * TOP, const float * POP, const int & Nclass)
  {
    float AC1 = 0.f;
    for (int i = 0; i < Nclass; ++i)
    {
      const float pi = (P[i] + TOP[i]) / (2.f * POP[i]);
      AC1 += pi * (1.f - pi);
    }
    return AC1;
  }
} get_PC_AC1;

struct
{
  auto operator() (const int & Nclass)
  {
    return 1.f / static_cast < float >(Nclass);
  }
} get_PC_S;

struct
{
  auto operator() (const float * P, const float * TOP, const float * POP, const int & Nclass)
  {
    float PI = 0.f;
    for (int i = 0; i < Nclass; ++i)
      PI += (P[i] + TOP[i]) / (2.f * POP[i]) * (2.f * POP[i]);
    return PI;
  }
} get_PI;

struct
{
  auto operator() (const float & PC_AC1, const float & overall_accuracy)
  {
    return (overall_accuracy - PC_AC1) / (1.f - PC_AC1);
  }
} get_AC1;

struct
{
  auto operator() (const float & PC_S, const float & overall_accuracy)
  {
    return (overall_accuracy - PC_S) / (1.f - PC_S);
  }
} get_S;

struct
{
  auto operator() (const float & overall_accuracy, const float & overall_random_accuracy, const float * POP)
  {
    return std :: sqrt( (overall_accuracy * (1.f - overall_accuracy) ) / (POP[0] * (1.f - overall_random_accuracy)*(1.f - overall_random_accuracy)) );
  }
} get_kappa_SE;

struct
{
  auto operator() (const float & overall_random_accuracy_unbiased, const float & overall_accuracy)
  {
    return (overall_accuracy - overall_random_accuracy_unbiased) / (1.f - overall_random_accuracy_unbiased);
  }
} get_kappa_unbiased;

struct
{
  auto operator() (const float & overall_accuracy)
  {
    return 2.f * overall_accuracy - 1.f;
  }
} get_kappa_no_prevalence;

struct
{
  auto operator() (const float & overall_kappa, const float & kappa_SE)
  {
    return overall_kappa - 1.96 * kappa_SE;
  }
} get_kappa_CI;

struct
{
  auto operator() (const float & overall_accuracy, const float * POP)
  {
    return std :: sqrt( (overall_accuracy * (1.f - overall_accuracy)) / POP[0]);
  }
} get_overall_accuracy_se;

struct
{
  auto operator() (const float & overall_accuracy, const float & overall_accuracy_se)
  {
    return overall_accuracy / overall_accuracy_se;
  }
} get_overall_accuracy_ci;

struct
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

struct
{
  auto operator() (const float & chi_square, const float * POP)
  {
    return chi_square / POP[0];
  }
} get_phi_square;

struct
{
  auto operator() (const float & phi_square, const int & Nclass)
  {
    return std::sqrt(phi_square / static_cast<float>(Nclass - 1));
  }
} get_cramers_V_calc;

struct
{
  auto operator() (const float * TOP, const float * POP, const int & Nclass)
  {
    return -std :: inner_product(TOP, TOP + Nclass, POP, 0.f, std :: plus < float >(), [](const float & item, const float & pop){float likelihood = item / pop; return likelihood * std :: log2(likelihood);});
  }
} get_response_entropy;

struct
{
  auto operator() (const float * P, const float * POP, const int & Nclass)
  {
    return -std :: inner_product(P, P + Nclass, POP, 0.f, std :: plus < float >(), [](const float & item, const float & pop){float likelihood = item / pop; return likelihood * std :: log2(likelihood);});
  }
} get_reference_entropy;

struct
{
  auto operator() (const float * TOP, const float * P, const float * POP, const int & Nclass)
  {
    float res = 0.f;
    for (int i = 0; i < Nclass; ++i)
      res += (P[i] / POP[i]) * std :: log2(TOP[i] / POP[i]);
    return -res;
  }
} get_cross_entropy;

struct
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

struct
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

struct
{
  auto operator() (const float & response_entropy, const float & conditional_entropy)
  {
    return response_entropy - conditional_entropy;
  }
} get_mutual_information;

struct
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

struct
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

struct
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

struct
{
  auto operator() (__unused const float * classes, const int & Nclass)
  {
    return static_cast< float >((Nclass - 1) * (Nclass - 1));
  }
} get_DF;

struct
{
  auto operator() (const float * jaccard_index, const int & Nclass)
  {
    return std :: accumulate(jaccard_index, jaccard_index + Nclass, 0.f);
  }
} get_overall_jaccard_index;

struct
{
  auto operator() (const float * TP, const float * POP, const int & Nclass)
  {
    return 1.f / POP[0] * (POP[0] - std :: accumulate(TP, TP + Nclass, 0.f));
  }
} get_hamming_loss;

struct
{
  auto operator() (const float * TP, const float * POP, const int & Nclass)
  {
    return POP[0] - std :: accumulate(TP, TP + Nclass, 0.f);
  }
} get_zero_one_loss;

struct
{
  auto operator() (const float * P, const float * POP, const int & Nclass)
  {
    return *std :: max_element(P, P + Nclass) / POP[0];
  }
} get_NIR;

struct
{
  auto operator() (__unused const float * TP, __unused const float * POP, __unused const int & Nclass, __unused const float & NIR)
  {
    float p_value = 0.f;
    const int x = std :: accumulate(TP, TP + Nclass, 0.f);

    for (int i = 0.f; i < x; ++i)
    {
      const int r = i < Nclass - i ? i : Nclass - i;

      int numer = 1;

      int iter = Nclass;
      while (iter < Nclass - r)
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

      p_value += ncr * std :: pow(NIR, i) * std :: pow(1 - NIR, Nclass - i);
    }

    return 1.f - p_value;
  }
} get_p_value;

struct
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

struct
{
  auto operator() (const float * TP, const float * TOP, const float * P, const float * CEN, const int & Nclass)
  {
    float overall_MCEN = 0.f;

    const float alpha = Nclass == 2 ? 0.f : 1.f;

    const float TOP_sum = std :: accumulate(TOP, TOP + Nclass, 0.f);
    const float TP_sum = std :: accumulate(TP, TP + Nclass, 0.f);

    for (int i = 0; i < Nclass; ++i)
    {
      const float up = TOP[i] + P[i] - TP[i];
      const float down = 2.f * TOP_sum - alpha * TP_sum;

      overall_MCEN += (up / down) * CEN[i];
    }

    return overall_MCEN;
  }
} get_overall_MCEN;

struct
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

struct
{
  auto operator() (const float * TOP, const int & Nclass)
  {
    return std :: accumulate(TOP, TOP + Nclass, 0.f) / Nclass;
  }

} get_RR;

struct
{
  auto operator() (const float * confusion_matrix, const float * TOP, const float * P, const int & Nclass)
  {
    float CBA = 0.f;
    for (int i = 0; i < Nclass; ++i)
      CBA += confusion_matrix[i * Nclass + i] / std :: max(TOP[i], P[i]);
    return CBA / Nclass;
  }

} get_CBA;

struct
{
  auto operator() (const float * AUC, const int & Nclass)
  {
    return std :: accumulate(AUC, AUC + Nclass, 0.f) / Nclass;
  }

} get_AUNU;

struct
{
  auto operator() (const float * P, const float * POP, const float * AUC, const int & Nclass)
  {
    float AUNP = 0.f;
    for (int i = 0; i < Nclass; ++i)
      AUNP += P[i] / POP[i] * AUC[i];
    return AUNP;
  }

} get_AUNP;

struct
{
  auto operator() (const float & mutual_information, const float & reference_entropy)
  {
    return mutual_information / reference_entropy;
  }
} get_RCI;

struct
{
  auto operator() (const float & chi_square, const float * POP)
  {
    return std :: sqrt (chi_square / (POP[0] + chi_square));
  }

} get_overall_pearson_C;


struct
{
  auto operator() (const float * TP, const float * FN, const int & Nclass)
  {
    const float TP_sum = std :: accumulate(TP, TP + Nclass, 0.f);
    const float FN_sum = std :: accumulate(FN, FN + Nclass, 0.f);
    return TP_sum / (TP_sum + FN_sum);
  }
} get_TPR_PPV_F1_micro;





#endif // __overall_stats_h__
