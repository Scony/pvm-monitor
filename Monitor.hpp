class Monitor
{
protected:
  class mutex
  {
  public:
    void lock();
    void unlock();
    mutex();

  private:
    int id;
  };

  // class condition
  // {
  //   void wait(...);
  //   void signal(...);
  // };

  // class sint			/* ? */
  // {
  //   /* operators */
  // };

private:
  static int mutexNextId;
};
