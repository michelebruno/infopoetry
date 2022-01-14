import * as React from 'react';
import {useForm} from 'react-hook-form';
import Seo from '../components/Seo';
import Layout from '../components/Layout';

// markup
function IndexPage() {
  const {
    register,
    handleSubmit,
    watch,
    formState: {errors},
  } = useForm();

  async function onSubmit(data) {
    let response = await fetch(
      `https://michelebruno.herokuapp.com/infopoetry/keyword/${data.keyword}`,
      {
        mode: 'no-cors', // no-cors, *cors, same-origin
        headers: {
          // 'Content-Type': 'application/x-www-form-urlencoded',
        },
        redirect: 'follow', // manual, *follow, error,
      }
    );

    response = await response.json();

  }

  return (
    <Layout>
      <Seo />
      <h1 className="text-4xl">Common secrets</h1>

      <div className="w-full">
        <form onSubmit={handleSubmit(onSubmit)}>
          <input
            type="text"
            className="border rounded p-1"
            {...register('keyword', {required: true})}
          />
          <button type="submit">Invia</button>
        </form>
      </div>
    </Layout>
  );
}

export default IndexPage;
