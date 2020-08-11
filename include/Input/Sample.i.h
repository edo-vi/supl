///@author EZ
///@date July 2020
///@version 0.1
///@file Sample.i.h
///@brief Declaration of Sample, SlicedSample and SlicedSettedSample
#pragma once

namespace sample {
template <typename T, typename Q> uint64_t Sample<T, Q>::size() const {
  return uint64_t{_arr.size()};
};

template <typename T, typename Q>
LabeledInstance<T, Q> Sample<T, Q>::operator[](int64_t index) const {
  return _arr[index];
}

template <typename T, typename Q>
LabeledInstance<T, Q> Sample<T, Q>::begin() const {
  return _arr.begin();
}

template <typename T, typename Q>
LabeledInstance<T, Q> Sample<T, Q>::end() const {
  return _arr.end();
}

template <typename T, typename Q>
ValidationSample<T, Q> Sample<T, Q>::split(uint64_t k) {
  assert(k < size());

  auto vs = ValidationSample<T, Q>();
  vs.test = Sample<T, Q>(
      std::vector<LabeledInstance<T, Q>>(_arr.begin(), _arr.begin() + k));
  vs.training = Sample<T, Q>(std::vector<LabeledInstance<T, Q>>(
      _arr.begin() + k, _arr.begin() + _arr.size() - 1));
  return vs;
};

template <typename T, typename Q> void Sample<T, Q>::shuffle() {
  std::random_device rdev{};
  std::mt19937 gen{rdev()};
  std::shuffle(_arr.begin(), _arr.end(), gen);
}

template <typename T, typename Q>
Sample<T, Q> sampleFromCsv(const std::string &filename) {

  std::vector<LabeledInstance<T, Q>> inputs{};

  rapidcsv::Document doc(filename, rapidcsv::LabelParams(-1, -1));

  auto rows = doc.GetRowCount();
  auto columns = doc.GetColumnCount();

  for (uint64_t i = 0; i < rows; i++) {
    std::vector<T> data{};

    uint64_t j = 0;
    for (; j < columns - 1; j++) {
      data.push_back(doc.GetCell<T>(j, i));
    }

    // remove leading whitespaces in the instances if T is a string
    if constexpr (std::is_same<T, std::string>::value) {
      for (uint k = 0; k < data.size(); k++) {
        const auto b = data[k].find_first_not_of(" \t");
        if (b == std::string::npos)
          throw; // empty or all whitespaces

        const auto e = data[k].size() - 1;
        const auto r = e - b + 1;

        data[k] = data[k].substr(b, r);
      }
    }

    Q label = doc.GetCell<Q>(j, i);
    // remove leading whitespaces in the label if it is a string
    if constexpr (std::is_same<Q, std::string>::value) {
      const auto b = label.find_first_not_of(" \t");
      if (b == std::string::npos)
        throw; // empty or all whitespaces

      const auto e = label.size() - 1;
      const auto r = e - b + 1;

      label = label.substr(b, r);
    }
    inputs.push_back(LabeledInstance<T, Q>(data, label));
  }
  return Sample<T, Q>(inputs);
}

template <typename T, typename Q, int k>
SlicedSettedSample<T, Q, k> SlicedSample<T, Q, k>::set(int s) {
  return SlicedSettedSample<T, Q, k>(_sample, s);
}

template <typename T, typename Q, int k>
sample::Sample<T, Q> SlicedSettedSample<T, Q, k>::trainingSet() {
  auto training = std::vector<input::LabeledInstance<T, Q>>();
  for (uint64_t i = 0; i < this->_sample.size(); i++) {
    if (i < _startidx || i > _endidx) {
      training.push_back(this->_sample[i]);
    };
  }
  return Sample<T, Q>(training);
};

template <typename T, typename Q, int k>
sample::Sample<T, Q> SlicedSettedSample<T, Q, k>::validationSet() {
  auto validation = std::vector<input::LabeledInstance<T, Q>>();

  for (uint64_t i = 0; i < this->_sample.size(); i++) {
    if (i >= _startidx && i <= _endidx) {
      validation.push_back(this->_sample[i]);
    }
  }
  return Sample<T, Q>(validation);
};
} // namespace sample