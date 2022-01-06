module.exports = {
  content: [
    './public/**/*.html',
    './src/**/*.{js,jsx,ts,tsx,vue,css,mdx}',
    './src/**/**/*.{js,jsx,ts,tsx,vue,css,mdx}',
  ],
  theme: {
    extend: {
      colors: {
        black: '#242424',
        brand: '#FFA500', // 'rgb(240 120 48)',
      },
      borderColor: {
        DEFAULT: '#242424',
      },
      transitionDuration: {
        DEFAULT: '600ms',
      },
    },
  },
  variants: {
    extend: {},
  },
};
